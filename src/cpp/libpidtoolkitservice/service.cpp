#include <sstream>
#include <memory>
#include <vector>

#include <MQTTClient.h>

#include <gos/pid/toolkit/setting.h>
#include <gos/pid/toolkit/service/service.h>
#include <gos/pid/toolkit/service/setting.h>
#include <gos/pid/toolkit/service/options.h>
#include <gos/pid/toolkit/service/subscriptions.h>
#include <gos/pid/toolkit/reporting.h>

namespace gpt = ::gos::pid::toolkit;

namespace gptsc = ::gos::pid::toolkit::setting::communication;

namespace gptr = ::gos::pid::toolkit::reporting;

namespace gos {
namespace pid {
namespace toolkit {
namespace service {

static MQTTClient _client = nullptr;

namespace callbacks {
namespace message {
static void delivered(void* context, MQTTClient_deliveryToken dt);
static int arrived(void* context, char* topicname, int topiclen, MQTTClient_message* message);
} // namespace message
namespace connection {
static void lost(void* context, char* cause);
} // namespace connection
} // namespace callbacks

bool create() {
  int rc;

  options::create();
  std::string address = gpt::service::setting::address();

  gpt::service::subscriptions::definitions::create(
    gpt::setting::communication::mqtt::topic::prefix.c_str());

  gptr::Stream repstr;
  if ((rc = MQTTClient_create(
    &_client,
    address.c_str(),
    gpt::setting::communication::mqtt::client::id.c_str(),
    MQTTCLIENT_PERSISTENCE_NONE,
    nullptr)) == MQTTCLIENT_SUCCESS) {
    if ((rc = MQTTClient_setCallbacks(
      _client,
      nullptr,
      callbacks::connection::lost,
      callbacks::message::arrived,
      callbacks::message::delivered)) == MQTTCLIENT_SUCCESS) {
      repstr << "Service created MQTT client with address as " << address;
      gptr::information::report(repstr);
      return true;
    }
    repstr << "Service MQTT client set callback failed: " << MQTTClient_strerror(rc);
  } else {
    repstr << "Service failed to create MQTT client: " << MQTTClient_strerror(rc);
  }
  gptr::error::report(repstr);
  return false;
}

void shutdown() {
  if (_client) {
    if (MQTTClient_isConnected(_client)) {
      stop();
    }

    MQTTClient_destroy(&_client);
    _client = nullptr;
    gptr::information::report("Service MQTT client shutdown");
  } else {
    gptr::warning::report("Service shutdown for undefined MQTT client");
  }
}

bool start() {
  int rc;

  gpt::service::subscriptions::Subscriptions& subscriptions =
    gpt::service::subscriptions::definitions::get();

  MQTTClient_connectOptions& options = gpt::service::options::get();

  if ((rc = MQTTClient_connect(_client, &options)) == MQTTCLIENT_SUCCESS) {
    gptr::information::report("Service MQTT client connected");
    for (const std::string item : subscriptions) {
      const char* subscription = item.c_str();
      gptr::Stream substr;
      if ((rc = MQTTClient_subscribe(
        _client,
        subscription,
        gpt::setting::communication::mqtt::qos)) == MQTTCLIENT_SUCCESS) {
        gpt::service::subscriptions::active::add(subscription);
        substr << "Service MQTT client subscribed to " << subscription;
        gptr::information::report(substr);
      } else {
        substr << "Service MQTT client failed to subscribe to "
          << subscription << ": "  << MQTTClient_strerror(rc);
        gptr::error::report(substr);
        return false;
      }
    }
  } else {
    gptr::Stream conerrstr;
    conerrstr << "Service MQTT client connected failed: "
      << MQTTClient_strerror(rc);
    gptr::error::report(conerrstr);
    return false;
  }

  return true;
}

bool stop() {
  int rc;

  gpt::service::subscriptions::Subscriptions active;
  gpt::service::subscriptions::active::get(active);

  for (const std::string item : active) {
    const char* subscription = item.c_str();
    if ((rc = MQTTClient_unsubscribe(_client, subscription)) == MQTTCLIENT_SUCCESS) {
      gpt::service::subscriptions::active::remove(subscription);
    }
  }

  if ((rc = MQTTClient_disconnect(_client, gptsc::mqtt::connection::timeout)) == MQTTCLIENT_SUCCESS) {
    return true;
  }

  return false;
}


namespace callbacks {
namespace message {

void delivered(void* context, MQTTClient_deliveryToken dt) {
  gptr::Stream infstr;
  infstr << "Service MQTT delivered token " << dt;
  gptr::verbose::report(infstr);
}

int arrived(void* context, char* topicname, int topiclen, MQTTClient_message* message) {
  std::unique_ptr<std::string> topicptr;
  gptr::Stream infstr;
  if (topiclen) {
    topicptr = std::make_unique<std::string>(topicname, topiclen);
  } else {
    topicptr = std::make_unique<std::string>(topicname);
  }
  std::string topic(*topicptr);
  char* payload = reinterpret_cast<char*>(message->payload);
  std::string payloadtext(payload, message->payloadlen);
  infstr << "Service MQTT arrive for topic " << topic << " message " << message;
  gptr::verbose::report(infstr);
  MQTTClient_freeMessage(&message);
  MQTTClient_free(topicname);
  return 1;
}

} // namespace message
namespace connection {

void lost(void* context, char* cause) {
  gptr::Stream infstr;
  infstr << "Service MQTT connection lost: " << cause;
  gptr::warning::report(infstr);
}

} // namespace connection
} // namespace callbacks


}
}
}
}
