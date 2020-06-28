#include <modbus.h>

#include <gos/pid/toolkit/serial.h>

#include <gos/pid/arduino/modbus/master.h>

#define GOS_ARDT_SET_FL modbus_set_float
#define GOS_ARDT_GET_FL modbus_get_float

//#define GOS_DL_PR_COILS 1
//#define GOS_DL_PR_DISCRETE 1
#define GOS_DL_PR_HOLDING 0x0010
#define GOS_DL_PR_INPUT 0x000A

#define GOS_TC_IRA_OUTPUT     0x0000
#define GOS_TC_IRA_TEMP       0x0001
#define GOS_TC_IRA_ERROR      0x0003
#define GOS_TC_IRA_INTEGRAL   0x0005
#define GOS_TC_IRA_DERIVATIVE 0x0007
#define GOS_TC_IRA_STATUS     0x0009

#define GOS_TC_HRA_INTERVAL   0x0000
#define GOS_TC_HRA_MANUAL     0x0001
#define GOS_TC_HRA_SETPOINT   0x0002
#define GOS_TC_HRA_KP         0x0004
#define GOS_TC_HRA_I          0x0006
#define GOS_TC_HRA_D          0x0008
#define GOS_TC_HRA_MIN_SENS   0x000A
#define GOS_TC_HRA_MAX_SENS   0x000C
#define GOS_TC_HRA_TIME_TUNE  0x000E
#define GOS_TC_HRA_FORCE      0x000F

namespace gp = ::gos::pid;
namespace gpa = ::gos::pid::arduino;
namespace gpat = ::gos::pid::arduino::types;
namespace gpam = ::gos::pid::arduino::modbus;
namespace gpamt = ::gos::pid::arduino::modbus::types;

namespace gpt = ::gos::pid::toolkit;

namespace gos {
namespace pid {
namespace arduino {
namespace modbus {
namespace master {

namespace report {
namespace error {
gpt::type::error_number _no;
std::string _last;
gpt::type::error_number errorno() {
  return _no;
}
std::string last() {
  return _last;
}
} // namespace error
} // namespace report

namespace details {
#ifdef GOS_DL_PR_COILS
static uint8_t _coils[GOS_DL_PR_COILS];
#endif
#ifdef GOS_DL_PR_DISCRETE
static uint8_t _discrete[GOS_DL_PR_DISCRETE];
#endif
static uint16_t _holding[GOS_DL_PR_HOLDING];
static uint16_t _input[GOS_DL_PR_INPUT];
static modbus_t* _modbus = nullptr;
} // namespace details

gpamt::result initialize(
  const char* device,
  const int& baud,
  const int& slaveid,
  const char& parity,
  const int& data_bit,
  const int& stop_bit) {
  ::std::string port = gpt::serial::compensate::port(device);
  details::_modbus = modbus_new_rtu(
    port.c_str(),
    baud,
    parity,
    data_bit,
    stop_bit);
  if (details::_modbus != nullptr) {
    int result = modbus_set_slave(details::_modbus, slaveid);
    return gpam::types::result::success;
  } else {
    return gpam::types::result::failure;
  }
}

gpamt::result connect() {
  int result;
  if (details::_modbus) {
    result = modbus_connect(details::_modbus);
    if (result >= 0) {
      return gpam::types::result::success;
    } else {
      report::error::_no = errno;
      report::error::_last = modbus_strerror(report::error::_no);
      return gpam::types::result::failure;
    }
  } else {
    return gpam::types::result::uninitialized;
  }
}

gpamt::result disconnect() {
  if (details::_modbus) {
    ::modbus_close(details::_modbus);
    return gpam::types::result::success;
  } else {
    return gpam::types::result::uninitialized;
  }
}

gpamt::result shutdown() {
  if (details::_modbus) {
    ::modbus_free(details::_modbus);
    details::_modbus = nullptr;
    return gpam::types::result::success;
  } else {
    return gpam::types::result::uninitialized;
  }
}

namespace read {
gpamt::result input(gpamt::registry::Input& input) {
  if (details::_modbus) {
    int result = ::modbus_read_input_registers(
      details::_modbus,
      0,
      GOS_DL_PR_INPUT,
      details::_input);
    if (result >= 0) {
      input.Output = details::_input[GOS_TC_IRA_OUTPUT];
      input.Temperature = GOS_ARDT_GET_FL(
        details::_input + GOS_TC_IRA_TEMP);
      input.Error = GOS_ARDT_GET_FL(
        details::_input + GOS_TC_IRA_ERROR);
      input.Integral = GOS_ARDT_GET_FL(
        details::_input + GOS_TC_IRA_INTEGRAL);
      input.Derivative = GOS_ARDT_GET_FL(
        details::_input + GOS_TC_IRA_DERIVATIVE);
      input.Status = details::_input[GOS_TC_IRA_STATUS];
      return gpam::types::result::success;
    } else {
      report::error::_no = errno;
      report::error::_last = modbus_strerror(report::error::_no);
      report::error::_last = "Failed to read input registers: " +
        report::error::_last;
      return gpam::types::result::failure;
    }
  } else {
    return gpam::types::result::uninitialized;
  }
}
gpamt::result holding(gpamt::registry::Holding& holding) {
  if (details::_modbus) {
    int result = ::modbus_read_registers(
      details::_modbus,
      0,
      GOS_DL_PR_HOLDING,
      details::_holding);
    if (result >= 0) {
      holding.Interval = details::_holding[GOS_TC_HRA_INTERVAL];
      holding.Manual = details::_holding[GOS_TC_HRA_MANUAL];
      holding.Setpoint = GOS_ARDT_GET_FL(
        details::_holding + GOS_TC_HRA_SETPOINT);
      holding.Kp = GOS_ARDT_GET_FL(
        details::_holding + GOS_TC_HRA_KP);
      holding.Ki = GOS_ARDT_GET_FL(
        details::_holding + GOS_TC_HRA_I);
      holding.Kd = GOS_ARDT_GET_FL(
        details::_holding + GOS_TC_HRA_D);
      holding.SensorMinimum = GOS_ARDT_GET_FL(
        details::_holding + GOS_TC_HRA_MIN_SENS);
      holding.SensorMaximum = GOS_ARDT_GET_FL(
        details::_holding + GOS_TC_HRA_MAX_SENS);
      holding.TimeTune = details::_holding[GOS_TC_HRA_TIME_TUNE];
      holding.Force = details::_holding[GOS_TC_HRA_FORCE];
      return gpam::types::result::success;
    } else {
      report::error::_no = errno;
      report::error::_last = modbus_strerror(report::error::_no);
      report::error::_last = "Failed to read holding registers: " +
        report::error::_last;
      return gpam::types::result::failure;
    }
  } else {
    return gpam::types::result::uninitialized;
  }
}
} // namespace read

namespace write {
gpamt::result holding(const gpamt::registry::Holding& holding) {
  if (details::_modbus) {
    details::_holding[GOS_TC_HRA_INTERVAL] = holding.Interval;
    details::_holding[GOS_TC_HRA_MANUAL] = holding.Manual;
    GOS_ARDT_SET_FL(holding.Setpoint, details::_holding + GOS_TC_HRA_SETPOINT);
    GOS_ARDT_SET_FL(holding.Kp, details::_holding + GOS_TC_HRA_KP);
    GOS_ARDT_SET_FL(holding.Ki, details::_holding + GOS_TC_HRA_I);
    GOS_ARDT_SET_FL(holding.Kd, details::_holding + GOS_TC_HRA_D);
    GOS_ARDT_SET_FL(holding.SensorMinimum,
      details::_holding + GOS_TC_HRA_MIN_SENS);
    GOS_ARDT_SET_FL(holding.SensorMaximum,
      details::_holding + GOS_TC_HRA_MAX_SENS);
    details::_holding[GOS_TC_HRA_TIME_TUNE] = holding.TimeTune;
    details::_holding[GOS_TC_HRA_FORCE] = holding.Force;
    int result = ::modbus_write_registers(
      details::_modbus,
      0,
      GOS_DL_PR_HOLDING,
      details::_holding);
    if (result >= 0) {
      return gpam::types::result::success;
    } else {
      return gpam::types::result::failure;
    }
  } else {
    return gpam::types::result::uninitialized;
  }
}
gpamt::result interval(const gpat::Unsigned& interval) {
  if (details::_modbus) {
    int result = ::modbus_write_register(
      details::_modbus,
      GOS_TC_HRA_INTERVAL,
      interval);
    if (result > 0) {
      return gpam::types::result::success;
    } else {
      return gpam::types::result::failure;
    }
  } else {
    return gpam::types::result::uninitialized;
  }
}
gpamt::result manual(const gpat::Unsigned& manual) {
  if (details::_modbus) {
    int result = ::modbus_write_register(
      details::_modbus,
      GOS_TC_HRA_MANUAL,
      manual);
    if (result > 0) {
      return gpam::types::result::success;
    } else {
      return gpam::types::result::failure;
    }
  } else {
    return gpam::types::result::uninitialized;
  }
}
gpamt::result setpoint(const gpat::Real& setpoint) {
  if (details::_modbus) {
    GOS_ARDT_SET_FL(setpoint, details::_holding + GOS_TC_HRA_SETPOINT);
    int result = ::modbus_write_registers(
      details::_modbus,
      GOS_TC_HRA_SETPOINT,
      2,
      details::_holding + GOS_TC_HRA_SETPOINT);
    if (result > 0) {
      return gpam::types::result::success;
    } else {
      return gpam::types::result::failure;
    }
  } else {
    return gpam::types::result::uninitialized;
  }
}
gpamt::result kp(const gpat::Real& kp) {
  if (details::_modbus) {
    GOS_ARDT_SET_FL(kp, details::_holding + GOS_TC_HRA_KP);
    int result = ::modbus_write_registers(
      details::_modbus,
      GOS_TC_HRA_KP,
      2,
      details::_holding + GOS_TC_HRA_KP);
    if (result > 0) {
      return gpam::types::result::success;
    } else {
      return gpam::types::result::failure;
    }
  } else {
    return gpam::types::result::uninitialized;
  }
}
gpamt::result ki(const gpat::Real& ki) {
  if (details::_modbus) {
    GOS_ARDT_SET_FL(ki, details::_holding + GOS_TC_HRA_I);
    int result = ::modbus_write_registers(
      details::_modbus,
      GOS_TC_HRA_I,
      2,
      details::_holding + GOS_TC_HRA_I);
    if (result > 0) {
      return gpam::types::result::success;
    } else {
      return gpam::types::result::failure;
    }
  } else {
    return gpam::types::result::uninitialized;
  }
}
gpamt::result kd(const gpat::Real& kd) {
  if (details::_modbus) {
    GOS_ARDT_SET_FL(kd, details::_holding + GOS_TC_HRA_D);
    int result = ::modbus_write_registers(
      details::_modbus,
      GOS_TC_HRA_D,
      2,
      details::_holding + GOS_TC_HRA_D);
    if (result > 0) {
      return gpam::types::result::success;
    } else {
      return gpam::types::result::failure;
    }
  } else {
    return gpam::types::result::uninitialized;
  }
}

gpamt::result tuning(
  const gpat::Real& kp,
  const gpat::Real& ki) {
  if (details::_modbus) {
    GOS_ARDT_SET_FL(kp, details::_holding + GOS_TC_HRA_KP);
    GOS_ARDT_SET_FL(ki, details::_holding + GOS_TC_HRA_I);
    int result = ::modbus_write_registers(
      details::_modbus,
      GOS_TC_HRA_KP,
      4,
      details::_holding + GOS_TC_HRA_KP);
    if (result > 0) {
      return gpam::types::result::success;
    } else {
      return gpam::types::result::failure;
    }
  } else {
    return gpam::types::result::uninitialized;
  }
}

gpamt::result tuning(
  const gpat::Real& kp,
  const gpat::Real& ki,
  const gpat::Real& kd) {
  if (details::_modbus) {
    GOS_ARDT_SET_FL(kp, details::_holding + GOS_TC_HRA_KP);
    GOS_ARDT_SET_FL(ki, details::_holding + GOS_TC_HRA_I);
    GOS_ARDT_SET_FL(kd, details::_holding + GOS_TC_HRA_D);
    int result = ::modbus_write_registers(
      details::_modbus,
      GOS_TC_HRA_KP,
      6,
      details::_holding + GOS_TC_HRA_KP);
    if (result > 0) {
      return gpam::types::result::success;
    } else {
      return gpam::types::result::failure;
    }
  } else {
    return gpam::types::result::uninitialized;
  }
}

gpamt::result sensor(
  const gpat::Real& minimum,
  const gpat::Real& maximum) {
  if (details::_modbus) {
    GOS_ARDT_SET_FL(minimum, details::_holding + GOS_TC_HRA_MIN_SENS);
    GOS_ARDT_SET_FL(maximum, details::_holding + GOS_TC_HRA_MAX_SENS);
    int result = ::modbus_write_registers(
      details::_modbus,
      GOS_TC_HRA_MIN_SENS,
      4,
      details::_holding + GOS_TC_HRA_MIN_SENS);
    if (result > 0) {
      return gpam::types::result::success;
    } else {
      return gpam::types::result::failure;
    }
  } else {
    return gpam::types::result::uninitialized;
  }
}

gpamt::result time(const gpat::Unsigned& tuning) {
  if (details::_modbus) {
    int result = ::modbus_write_register(
      details::_modbus,
      GOS_TC_HRA_TIME_TUNE,
      tuning);
    if (result > 0) {
      return gpam::types::result::success;
    } else {
      return gpam::types::result::failure;
    }
  } else {
    return gpam::types::result::uninitialized;
  }
}

gpamt::result force(const gpat::Unsigned& force) {
  if (details::_modbus) {
    int result = ::modbus_write_register(
      details::_modbus,
      GOS_TC_HRA_FORCE,
      force);
    if (result > 0) {
      return gpam::types::result::success;
    } else {
      return gpam::types::result::failure;
    }
  } else {
    return gpam::types::result::uninitialized;
  }
}

} // namespace write

} // namespace master
} // namespace modbus
} // namespace arduino
} // namespace pid
} // namespace gos
