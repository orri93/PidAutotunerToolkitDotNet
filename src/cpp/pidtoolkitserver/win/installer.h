#ifndef GOS_PID_TOOLKIT_SERVICE_WIN_INSTALLER_H_
#define GOS_PID_TOOLKIT_SERVICE_WIN_INSTALLER_H_

//
//  FUNCTION: SvcInstall
//
//  PURPOSE: Installs the service
//
//  PARAMETERS:
//    none
//
//  RETURN VALUE:
//    none
//
//  COMMENTS:
//
void SvcInstall();


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
//
void SvcUninstall();


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
void SvcQueryConfig();

namespace gos {
namespace pid {
namespace toolkit {
namespace service {
namespace windows {
namespace installer {

void install();
void uninstall();

namespace query {
void configuration();
}

}
}
}
}
}
}

#endif
