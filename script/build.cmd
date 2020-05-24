@ECHO OFF

SETLOCAL ENABLEEXTENSIONS

SET GOS_ROOT_DIR=..
CALL:MakeAbsolute GOS_ROOT_DIR "%~dp0"

SET GOS_PROJECT_NAME=PID Toolkit

SET GOS_EXE_CMAKE=cmake.exe
SET GOS_EXE_CTEST=ctest.exe

SET GOS_DIA_EXE_PATH=C:/Program Files (x86)/Dia/bin/dia.exe

ECHO ---------------------------------------------------------------------------

ECHO Build script for the %GOS_PROJECT_NAME% project

ECHO %GOS_PROJECT_NAME% root directory is defined as %GOS_ROOT_DIR%

REM Set build variables
SET GOS_BUILD_CONFIG=RelWithDebInfo

IF "%1" == "" GOTO gos_no_build_number
SET GOS_BUILD_NUMBER=%1
GOTO gos_build_number_done
:gos_no_build_number
SET GOS_BUILD_NUMBER=0
:gos_build_number_done

SET GOS_PROJECT_BUILD_DIR=%GOS_ROOT_DIR%\build\%GOS_BUILD_CONFIG%
SET GOS_PROJECT_ARTIFACTS_DIR=%GOS_ROOT_DIR%\artifacts\%GOS_BUILD_CONFIG%
SET GOS_PROJECT_INCLUDE_DIR=%GOS_ROOT_DIR%\include

SET GOS_CMAKE_SYSTEM=Visual Studio 16 2019
SET GOS_CMAKE_PLATFORM=x64

REM -DGOS_DEPLOY_PDB_FILES:BOOL=ON ^
REM -DGOS_BUILD_NUMBER=%GOS_BUILD_NUMBER% ^
REM -Dgtest_force_shared_crt:BOOL=ON ^

SET GOS_CMAKE_CREATE_OPTIONS=-DBUILD_DOCS:BOOL=ON ^
-DGOS_DEPLOY_PDB_FILES:BOOL=ON ^
-DDOXYGEN_DIA_EXECUTABLE:FILEPATH="%GOS_DIA_EXE_PATH%" ^
-DCMAKE_INSTALL_PREFIX:PATH="%GOS_PROJECT_ARTIFACTS_DIR%" ^
-DCMAKE_BUILD_TYPE=%GOS_BUILD_CONFIG% ^
-G "%GOS_CMAKE_SYSTEM%" ^
-A %GOS_CMAKE_PLATFORM% "%GOS_ROOT_DIR%"

ECHO - GOS Build number is defined as %GOS_BUILD_NUMBER%
ECHO - Install path is defined as "%GOS_PROJECT_ARTIFACTS_DIR%"
ECHO - CMake buld system is defined as "%GOS_CMAKE_SYSTEM%"
ECHO - CMake buld platform is defined as "%GOS_CMAKE_PLATFORM%"
ECHO - CMake buld directory is defined as "%GOS_PROJECT_BUILD_DIR%"
ECHO - CMake buld configuration is defined as "%GOS_BUILD_CONFIG%"

SET GOS_CMAKE_BUILD_OPTIONS=--build "%GOS_PROJECT_BUILD_DIR%" --target ALL_BUILD --config %GOS_BUILD_CONFIG%
REM SET GOS_CMAKE_BUILD_OPTIONS=--build "%GOS_PROJECT_BUILD_DIR%" --target ALL_BUILD --config %GOS_BUILD_CONFIG%
SET GOS_CMAKE_INSTALL_OPTIONS=--build "%GOS_PROJECT_BUILD_DIR%" --target install --config %GOS_BUILD_CONFIG%
SET GOS_CMAKE_DOXYGEN_OPTIONS=--build "%GOS_PROJECT_BUILD_DIR%" --target doxygetpidtoolkit --config %GOS_BUILD_CONFIG%

SET GOS_CTEST_OPTIONS=--build-config %GOS_BUILD_CONFIG%

IF EXIST "%GOS_PROJECT_BUILD_DIR%" (
  ECHO The build folder already exists so deleting the old
  "%GOS_EXE_CMAKE%" -E remove_directory "%GOS_PROJECT_BUILD_DIR%"
)

IF EXIST "%GOS_PROJECT_ARTIFACTS_DIR%" (
  ECHO The artifacts folder already exists so deleting the old
  "%GOS_EXE_CMAKE%" -E remove_directory "%GOS_PROJECT_ARTIFACTS_DIR%"
)

ECHO Creating a build folder %GOS_PROJECT_BUILD_DIR%
"%GOS_EXE_CMAKE%" -E make_directory "%GOS_PROJECT_BUILD_DIR%"

ECHO *** Creating a Build
SET GOS_CMAKE_CREATE_BUILD_CMD="%GOS_EXE_CMAKE%" -E chdir "%GOS_PROJECT_BUILD_DIR%" "%GOS_EXE_CMAKE%" %GOS_CMAKE_CREATE_OPTIONS%
ECHO %GOS_CMAKE_CREATE_BUILD_CMD%
%GOS_CMAKE_CREATE_BUILD_CMD%

ECHO *** Building
SET GOS_CMAKE_BUILD_CMD="%GOS_EXE_CMAKE%" %GOS_CMAKE_BUILD_OPTIONS%
ECHO %GOS_CMAKE_BUILD_CMD%
%GOS_CMAKE_BUILD_CMD%

ECHO *** Generating API Documentation
SET GOS_CMAKE_DOXYGEN_CMD="%GOS_EXE_CMAKE%" %GOS_CMAKE_DOXYGEN_OPTIONS%
ECHO %GOS_CMAKE_DOXYGEN_CMD%
%GOS_CMAKE_DOXYGEN_CMD%

ECHO *** Testing
SET GOS_CMAKE_CTEST_CMD="%GOS_EXE_CMAKE%" -E chdir "%GOS_PROJECT_BUILD_DIR%" "%GOS_EXE_CTEST%" %GOS_CTEST_OPTIONS%
ECHO %GOS_CMAKE_CTEST_CMD%
%GOS_CMAKE_CTEST_CMD%

ECHO *** Installing
SET GOS_CMAKE_INSTALL_CMD="%GOS_EXE_CMAKE%" %GOS_CMAKE_INSTALL_OPTIONS%
ECHO %GOS_CMAKE_INSTALL_CMD%
%GOS_CMAKE_INSTALL_CMD%




REM Done
GOTO:EOF


::----------------------------------------------------------------------------------
:: Function declarations
:: Handy to read http://www.dostips.com/DtTutoFunctions.php for how dos functions
:: work.
::----------------------------------------------------------------------------------
:MakeAbsolute file base -- makes a file name absolute considering a base path
::                      -- file [in,out] - variable with file name to be converted, or file name itself for result in stdout
::                      -- base [in,opt] - base path, leave blank for current directory
:$created 20060101 :$changed 20080219 :$categories Path
:$source http://www.dostips.com
SETLOCAL ENABLEDELAYEDEXPANSION
set "src=%~1"
if defined %1 set "src=!%~1!"
set "bas=%~2"
if not defined bas set "bas=%cd%"
for /f "tokens=*" %%a in ("%bas%.\%src%") do set "src=%%~fa"
( ENDLOCAL & REM RETURN VALUES
    IF defined %1 (SET %~1=%src%) ELSE ECHO.%src%
)
EXIT /b