#ifndef GOS_PID_TOOLKIT_SERVICE_WIN_SERVICE_H_
#define GOS_PID_TOOLKIT_SERVICE_WIN_SERVICE_H_

// 
// Settings of the service
// 

// Internal name of the service
#define SERVICE_NAME             "PidToolkitService"

// Displayed name of the service
#define SERVICE_DISPLAY_NAME     "PID Toolkit Service"

// List of service dependencies - "dep1\0dep2\0\0"
#define SERVICE_DEPENDENCIES     ""

// The name of the account under which the service should run
#define SERVICE_ACCOUNT          "NT AUTHORITY\\LocalService"

// The password to the service account name
#define SERVICE_PASSWORD         NULL

#endif
