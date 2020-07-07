#include <cstdio>
#include <windows.h>

#include <win/service.h>
#include <win/installer.h>

namespace gptsw = ::gos::pid::toolkit::service::windows;

//
//  FUNCTION: SvcInstall
//
//  PURPOSE: Installs the service, and configure the service to trigger-start if applicable
//
//  PARAMETERS:
//    none
//
//  RETURN VALUE:
//    none
//
//  COMMENTS:
//    This function requires administrative privilege
//
void SvcInstall() {
	gptsw::installer::install();
}

//
//  FUNCTION: SvcUninstall
//
//  PURPOSE: Stops and removes the service
//
//  PARAMETERS:
//    none
//
//  RETURN VALUE:
//    none
//
//  COMMENTS:
//    This function requires administrative priviledge
//
void SvcUninstall() {
	gptsw::installer::uninstall();
}

//
//  FUNCTION: SvcQueryConfig
//
//  PURPOSE: Query the service status and trigger-start configuration
//
//  PARAMETERS:
//    none
//
//  RETURN VALUE:
//    none
//
//  COMMENTS:
//    This function does not require administrative priviledge
//
void SvcQueryConfig() {
	gptsw::installer::query::configuration();
}

namespace gos {
namespace pid {
namespace toolkit {
namespace service {
namespace windows {
namespace installer {

void install() {
	char szPath[MAX_PATH];
	if (GetModuleFileName(NULL, szPath, ARRAYSIZE(szPath)) == 0) {
		printf("GetModuleFileName failed w/err 0x%08lx\n", GetLastError());
		return;
	}

	// Open the local default service control manager database
	SC_HANDLE schSCManager = OpenSCManager(NULL, NULL,
		SC_MANAGER_CONNECT | SC_MANAGER_CREATE_SERVICE);
	if (!schSCManager) {
		printf("OpenSCManager failed w/err 0x%08lx\n", GetLastError());
		return;
	}

	// Install the service into SCM by calling CreateService
	SC_HANDLE schService = CreateService(
		schSCManager,                   // SCManager database
		SERVICE_NAME,                   // Name of service
		SERVICE_DISPLAY_NAME,           // Name to display
		SERVICE_CHANGE_CONFIG,          // Desired access
		SERVICE_WIN32_OWN_PROCESS,      // Service type
		SERVICE_DEMAND_START,           // Start type
		SERVICE_ERROR_NORMAL,           // Error control type
		szPath,                         // Service's binary
		NULL,                           // No load ordering group
		NULL,                           // No tag identifier
		SERVICE_DEPENDENCIES,           // Dependencies
		SERVICE_ACCOUNT,                // Service running account
		SERVICE_PASSWORD);              // Password of the account

	if (NULL != schService) {
		printf("%s installed.\n", SERVICE_DISPLAY_NAME);

#if defined(SERVICE_TRIGGER)
		// Check whether the current system supports service trigger start
		if (SupportServiceTriggerStart()) {
			// Configure service trigger start
			// Please note that the service handle (schService) must be opened or created 
			// with the SERVICE_CHANGE_CONFIG access right (see the above call to 
			// CreateService), otherwise, the function will fail with ERROR_ACCESS_DENIED. 

			printf("Configuring service trigger start...\n");

#if defined(SERVICE_TRIGGER_START_ON_USB)

			// Set the service to trigger-start when a generic USB disk becomes available
			if (!SetServiceTriggerStartOnUSBArrival(schService)) {
				printf("SetServiceTriggerStartOnUSBArrival failed w/err 0x%08lx\n",
					GetLastError());
			}

#elif defined(SERVICE_TRIGGER_START_ON_IP_ADDRESS)

			// Set the service to trigger-start when the first IP address becomes available, 
			// and trigger-stop when the last IP address becomes unavailable.
			if (!SetServiceTriggerStartOnIPAddressArrival(schService)) {
				printf("SetServiceTriggerStartOnIPAddressArrival failed w/err 0x%08lx\n",
					GetLastError());
			}

#elif defined(SERVICE_TRIGGER_START_ON_FIREWALL_PORT)

			// Set the service to trigger-start when a firewall port (UDP 5001 in this 
			// example) is opened, and trigger-stop when the a firewall port (UDP 5001 in 
			// this example) is closed. 
			if (!SetServiceTriggerStartOnFirewallPortEvent(schService)) {
				printf("SetServiceTriggerStartOnFirewallPortEvent failed w/err 0x%08lx\n",
					GetLastError());
			}

#endif
		} else {
			printf("The current system does not support trigger-start service.\n");
		}
#endif

		CloseServiceHandle(schService);
	} else {
		printf("CreateService failed w/err 0x%08lx\n", GetLastError());
	}

	CloseServiceHandle(schSCManager);
}

void uninstall() {
	// Open the local default service control manager database
	SC_HANDLE schSCManager = OpenSCManager(NULL, NULL, SC_MANAGER_CONNECT);
	if (!schSCManager) {
		printf("OpenSCManager failed w/err 0x%08lx\n", GetLastError());
		return;
	}

	// Open the service with delete, stop and query status permissions
	SC_HANDLE schService = OpenService(schSCManager, SERVICE_NAME,
		DELETE | SERVICE_STOP | SERVICE_QUERY_STATUS);

	if (NULL != schService) {
		// Try to stop the service
		SERVICE_STATUS ssSvcStatus;
		if (ControlService(schService, SERVICE_CONTROL_STOP, &ssSvcStatus)) {
			printf("Stopping %s.", SERVICE_DISPLAY_NAME);
			Sleep(1000);

			while (QueryServiceStatus(schService, &ssSvcStatus)) {
				if (ssSvcStatus.dwCurrentState == SERVICE_STOP_PENDING) {
					printf(".");
					Sleep(1000);
				} else break;
			}

			if (ssSvcStatus.dwCurrentState == SERVICE_STOPPED) {
				printf("\n%s stopped.\n", SERVICE_DISPLAY_NAME);
			} else {
				printf("\n%s failed to stop.\n", SERVICE_DISPLAY_NAME);
			}
		}

		// Now remove the service by calling DeleteService
		if (DeleteService(schService)) {
			printf("%s removed.\n", SERVICE_DISPLAY_NAME);
		} else {
			printf("DeleteService failed w/err 0x%08lx\n", GetLastError());
		}

		CloseServiceHandle(schService);
	} else {
		printf("OpenService failed w/err 0x%08lx\n", GetLastError());
	}

	CloseServiceHandle(schSCManager);
}

namespace query {
void configuration() {
	// Open the local default service control manager database
	SC_HANDLE schSCManager = OpenSCManager(NULL, NULL, SC_MANAGER_CONNECT);
	if (!schSCManager) {
		printf("OpenSCManager failed w/err 0x%08lx\n", GetLastError());
		return;
	}

	// Try to open the service to query its status and config
	SC_HANDLE schService = OpenService(schSCManager, SERVICE_NAME,
		SERVICE_QUERY_STATUS | SERVICE_QUERY_CONFIG);

	if (NULL != schService) {
		printf("%s was installed.\n", SERVICE_DISPLAY_NAME);

		DWORD cbBytesNeeded;

		// 
		// Query the status of the service
		// 

		SERVICE_STATUS_PROCESS ssp;
		if (QueryServiceStatusEx(schService, SC_STATUS_PROCESS_INFO, (LPBYTE)&ssp,
			sizeof(ssp), &cbBytesNeeded)) {
			printf("Service status: ");
			switch (ssp.dwCurrentState) {
			case SERVICE_STOPPED: printf("Stopped\n"); break;
			case SERVICE_RUNNING: printf("Running\n"); break;
			case SERVICE_PAUSED: printf("Paused\n"); break;
			case SERVICE_START_PENDING:
			case SERVICE_STOP_PENDING:
			case SERVICE_CONTINUE_PENDING:
			case SERVICE_PAUSE_PENDING: printf("Pending\n"); break;
			}
		} else {
			printf("QueryServiceStatusEx failed w/err 0x%08lx\n", GetLastError());
		}

#if defined(SERVICE_TRIGGER)
		// 
		// Query the trigger-start configuration of the service
		// 

		BOOL fIsTriggerStart;
		if (GetServiceTriggerInfo(schService, &fIsTriggerStart)) {
			printf("Is trigger-start: %s", fIsTriggerStart ? "Yes" : "No");
		} else {
			printf("GetServiceTriggerInfo failed w/err 0x%08lx\n", GetLastError());
		}
#endif

		CloseServiceHandle(schService);
	} else {
		DWORD dwErr = GetLastError();
		if (dwErr == ERROR_SERVICE_DOES_NOT_EXIST) {
			printf("%s was not installed.\n", SERVICE_DISPLAY_NAME);
		} else {
			printf("OpenService failed w/err 0x%08lx\n", dwErr);
		}
	}

	CloseServiceHandle(schSCManager);
}
}

}
}
}
}
}
}