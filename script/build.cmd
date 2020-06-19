@ECHO OFF

SETLOCAL ENABLEEXTENSIONS

SET GOS_ROOT_DIR=..
CALL:MakeAbsolute GOS_ROOT_DIR "%~dp0"

SET GOS_PROJECT_NAME=PID Toolkit

SET GOS_EXE_CMAKE=cmake.exe
SET GOS_EXE_CTEST=ctest.exe
SET GOS_QML_PLUGIN_DUMP_EXE=qmlplugindump
SET GOS_QML_PLUGIN_VERSION=1.0
SET GOS_QML_PLUGIN=Pid.Toolkit

SET GOS_BUILD_LOG_DIR=%GOS_ROOT_DIR%\var\log

SET GOS_DIA_EXE_PATH=C:/Program Files (x86)/Dia/bin/dia.exe

ECHO ---------------------------------------------------------------------------

ECHO Build script for the %GOS_PROJECT_NAME% project

ECHO %GOS_PROJECT_NAME% root directory is defined as %GOS_ROOT_DIR%

REM Set build variables
SET GOS_BUILD_CONFIG=RelWithDebInfo

IF "%1" == "noclean" GOTO gos_not_clean
IF "%1" == "notclean" GOTO gos_not_clean
IF "%1" == "Noclean" GOTO gos_not_clean
IF "%1" == "Notclean" GOTO gos_not_clean
IF "%1" == "noClean" GOTO gos_not_clean
IF "%1" == "notClean" GOTO gos_not_clean
IF "%1" == "NoClean" GOTO gos_not_clean
IF "%1" == "NotClean" GOTO gos_not_clean
GOTO gos_check_not_clean_done
:gos_not_clean
ECHO Not Clean detected
SET GOS_NOT_CLEAN=NotClean
SHIFT
:gos_check_not_clean_done

IF "%1" == "nobuild" GOTO gos_not_build
IF "%1" == "nobuilds" GOTO gos_not_build
IF "%1" == "notbuild" GOTO gos_not_build
IF "%1" == "notbuilds" GOTO gos_not_build
IF "%1" == "noBuild" GOTO gos_not_build
IF "%1" == "noBuilds" GOTO gos_not_build
IF "%1" == "notBuild" GOTO gos_not_build
IF "%1" == "notBuilds" GOTO gos_not_build
IF "%1" == "NoBuild" GOTO gos_not_build
IF "%1" == "NoBuilds" GOTO gos_not_build
IF "%1" == "NotBuild" GOTO gos_not_build
IF "%1" == "NotBuilds" GOTO gos_not_build
SET GOS_BUILDING=ON
GOTO gos_no_build_done
:gos_not_build
ECHO No Build detected
SET GOS_BUILDING=OFF
SHIFT
:gos_no_build_done

IF "%1" == "nodoc" GOTO gos_not_doc
IF "%1" == "nodocs" GOTO gos_not_doc
IF "%1" == "notdoc" GOTO gos_not_doc
IF "%1" == "notdocs" GOTO gos_not_doc
IF "%1" == "noDoc" GOTO gos_not_doc
IF "%1" == "noDocs" GOTO gos_not_doc
IF "%1" == "notDoc" GOTO gos_not_doc
IF "%1" == "notDocs" GOTO gos_not_doc
IF "%1" == "NoDoc" GOTO gos_not_doc
IF "%1" == "NoDocs" GOTO gos_not_doc
IF "%1" == "NotDoc" GOTO gos_not_doc
IF "%1" == "NotDocs" GOTO gos_not_doc
SET GOS_BUILD_DOCS=ON
GOTO gos_check_doc_done
:gos_not_doc
ECHO No Documentation detected
SET GOS_NOT_DOC=NotDoc
SET GOS_BUILD_DOCS=OFF
SHIFT
:gos_check_doc_done

IF "%1" == "" GOTO gos_no_build_number
SET GOS_BUILD_NUMBER=%1
GOTO gos_build_number_done
:gos_no_build_number
SET GOS_BUILD_NUMBER=0
:gos_build_number_done
SHIFT


REM Check and set environmental variables

REM Check for Latex pdfflatex
SET GOS_MIKTEX_PATH=C:\Program Files\MiKTeX 2.9\miktex\bin\x64
SET GOS_LATEX_IN_PATH_INDICATOR=%GOS_MIKTEX_PATH%
CALL:inPath GOS_LATEX_IN_PATH_INDICATOR && ( GOTO latex_in_path ) || ( GOTO latex_not_in_path )
:latex_in_path
ECHO The Latex bin folder is already in the path
GOTO latex_in_path_done
:latex_not_in_path
ECHO Putting the Latex bin folders into the path
SET PATH=%PATH%;%GOS_MIKTEX_PATH%
ECHO Testing PDF Latex by getting version information
pdflatex --version
:latex_in_path_done

REM Check for Python
SET GOS_PYTHON_IN_PATH_INDICATOR=C:\Python38\
CALL:inPath GOS_PYTHON_IN_PATH_INDICATOR && ( GOTO python_in_path ) || ( GOTO python_not_in_path )
:python_in_path
ECHO The Python bin folders is already in the path
GOTO python_in_path_done
:python_not_in_path
ECHO Putting the Python bin folders into the path
SET PATH=%PATH%;C:\Python38\;C:\Python38\Scripts\;C:\%USERPROFILE%\AppData\Roaming\Python\Scripts
:python_in_path_done

REM Check Qt
IF NOT DEFINED QTDIR GOTO qtdir_not_defined
  ECHO QT Dir already defined as %QTDIR%
  GOTO qtdir_defined
:qtdir_not_defined
  SET QTDIR=C:\Qt\5.14.2\msvc2017_64
  ECHO QT Dir not defined. Defined as %QTDIR%
:qtdir_defined
SET QT_BIN_DIR=%QTDIR%\bin
SET GOS_QT_IN_PATH_INDICATOR=%QT_BIN_DIR%
CALL:inPath GOS_QT_IN_PATH_INDICATOR && ( GOTO qt_in_path ) || ( GOTO qt_not_in_path )
:qt_in_path
ECHO The Qt bin folder is already in the path
GOTO qt_in_path_done
:qt_not_in_path
ECHO Putting the Qt bin folder into the path
SET PATH=%QT_BIN_DIR%;%PATH%
:qt_in_path_done

SET GOS_PROJECT_BUILD_DIR=%GOS_ROOT_DIR%\build\%GOS_BUILD_CONFIG%
SET GOS_PROJECT_ARTIFACTS_DIR=%GOS_ROOT_DIR%\artifacts\%GOS_BUILD_CONFIG%
SET GOS_PROJECT_INCLUDE_DIR=%GOS_ROOT_DIR%\include

REM SET GOS_QML_PLUGIN_BUILD_DIR=%GOS_PROJECT_BUILD_DIR%\plugin
REM SET GOS_QML_PLUGIN_BUILD_QML_TYPES_DESTINATION=%GOS_QML_PLUGIN_BUILD_DIR%\Pid\Toolkit\plugin.qmltypes
SET GOS_QML_PLUGIN_INSTALL_DIR=%GOS_PROJECT_ARTIFACTS_DIR%\plugin\empty
SET GOS_QML_PLUGIN_INSTALL_QML_TYPES_DESTINATION=%GOS_QML_PLUGIN_INSTALL_DIR%\Pid\Toolkit\plugin.qmltypes

SET GOS_CMAKE_SYSTEM=Visual Studio 16 2019
SET GOS_CMAKE_PLATFORM=x64

REM -DGOS_DEPLOY_PDB_FILES:BOOL=ON ^
REM -DGOS_BUILD_NUMBER=%GOS_BUILD_NUMBER% ^
REM -DGOS_PID_TOOLKIT_UI_PLUGIN_QML_TYPES:BOOL=ON ^
REM -Dgtest_force_shared_crt:BOOL=ON ^

SET GOS_CMAKE_CREATE_OPTIONS=^
--graphviz="%GOS_PROJECT_ARTIFACTS_DIR%\share\graphviz\pidtoolkit" ^
--log-level=DEBUG ^
-DBUILD_DOCS:BOOL=%GOS_BUILD_DOCS% ^
-DGOS_DEPLOY_PDB_FILES:BOOL=ON ^
-DGOS_PID_TOOLKIT_UI_PLUGIN_GENERATE_DUMMY:BOOL=ON ^
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

IF "%GOS_NOT_CLEAN%" == "NotClean" GOTO gos_do_not_clean
IF EXIST "%GOS_PROJECT_BUILD_DIR%" (
  ECHO The build folder already exists so deleting the old
  "%GOS_EXE_CMAKE%" -E remove_directory "%GOS_PROJECT_BUILD_DIR%"
)
IF EXIST "%GOS_PROJECT_ARTIFACTS_DIR%" (
  ECHO The artifacts folder already exists so deleting the old
  "%GOS_EXE_CMAKE%" -E remove_directory "%GOS_PROJECT_ARTIFACTS_DIR%"
)
:gos_do_not_clean

REM IF EXIST "%GOS_QML_PLUGIN_BUILD_QML_TYPES_DESTINATION%" (
REM   ECHO The plugin QML types for the build exists so deleting the old
REM   DEL "%GOS_QML_PLUGIN_BUILD_QML_TYPES_DESTINATION%"
REM )
IF EXIST "%GOS_QML_PLUGIN_INSTALL_QML_TYPES_DESTINATION%" (
  ECHO The plugin QML types for the install exists so deleting the old
  DEL "%GOS_QML_PLUGIN_INSTALL_QML_TYPES_DESTINATION%"
)

ECHO Creating a build folder %GOS_PROJECT_BUILD_DIR%
"%GOS_EXE_CMAKE%" -E make_directory "%GOS_PROJECT_BUILD_DIR%"

ECHO *** Creating a Build
SET GOS_CMAKE_CREATE_BUILD_CMD="%GOS_EXE_CMAKE%" -E chdir "%GOS_PROJECT_BUILD_DIR%" "%GOS_EXE_CMAKE%" %GOS_CMAKE_CREATE_OPTIONS%
ECHO %GOS_CMAKE_CREATE_BUILD_CMD%
%GOS_CMAKE_CREATE_BUILD_CMD%

IF "%GOS_BUILDING%" == "OFF" GOTO gos_do_not_build
ECHO *** Building
SET GOS_CMAKE_BUILD_CMD="%GOS_EXE_CMAKE%" %GOS_CMAKE_BUILD_OPTIONS%
ECHO %GOS_CMAKE_BUILD_CMD%
%GOS_CMAKE_BUILD_CMD%

REM ECHO *** Creating a Plugin QML Types for the Build
REM SET GOS_QML_PLUGIN_BUILD_DUMP_CMD="%GOS_QML_PLUGIN_DUMP_EXE%" -nonrelocatable -output "%GOS_QML_PLUGIN_BUILD_QML_TYPES_DESTINATION%" %GOS_QML_PLUGIN% %GOS_QML_PLUGIN_VERSION% "%GOS_QML_PLUGIN_BUILD_DIR%"
REM ECHO %GOS_QML_PLUGIN_BUILD_DUMP_CMD%
REM %GOS_QML_PLUGIN_BUILD_DUMP_CMD%

ECHO *** Testing
SET GOS_CMAKE_CTEST_CMD="%GOS_EXE_CMAKE%" -E chdir "%GOS_PROJECT_BUILD_DIR%" "%GOS_EXE_CTEST%" %GOS_CTEST_OPTIONS%
ECHO %GOS_CMAKE_CTEST_CMD%
%GOS_CMAKE_CTEST_CMD%
:gos_do_not_build

IF "%GOS_NOT_DOC%" == "NotDoc" GOTO gos_do_not_generate_doc
ECHO *** Generating API Documentation
SET GOS_CMAKE_DOXYGEN_CMD="%GOS_EXE_CMAKE%" %GOS_CMAKE_DOXYGEN_OPTIONS%
ECHO %GOS_CMAKE_DOXYGEN_CMD%
%GOS_CMAKE_DOXYGEN_CMD%
REM ECHO *** Generating PDF Documentation
REM SET GOS_DOXYGEN_BUILD_DIR=%GOS_PROJECT_BUILD_DIR%\doc\latex
REM ECHO Entering %GOS_DOXYGEN_BUILD_DIR%
REM PUSHD "%GOS_DOXYGEN_BUILD_DIR%"
REM ECHO Execute PDF Latex
REM ECHO pdflatex pdf
REM POPD
:gos_do_not_generate_doc

ECHO *** Installing
SET GOS_CMAKE_INSTALL_CMD="%GOS_EXE_CMAKE%" %GOS_CMAKE_INSTALL_OPTIONS%
ECHO %GOS_CMAKE_INSTALL_CMD%
%GOS_CMAKE_INSTALL_CMD%

ECHO *** Creating a Plugin QML Types for the Install
SET GOS_QML_PLUGIN_INSTALL_DUMP_CMD="%GOS_QML_PLUGIN_DUMP_EXE%" -nonrelocatable -output "%GOS_QML_PLUGIN_INSTALL_QML_TYPES_DESTINATION%" %GOS_QML_PLUGIN% %GOS_QML_PLUGIN_VERSION% "%GOS_QML_PLUGIN_INSTALL_DIR%"
ECHO %GOS_QML_PLUGIN_INSTALL_DUMP_CMD%
%GOS_QML_PLUGIN_INSTALL_DUMP_CMD%

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

:inPath pathVar
::
::  Tests if the path stored within variable pathVar exists within PATH.
::
::  The result is returned as the ERRORLEVEL:
::    0 if the pathVar path is found in PATH.
::    1 if the pathVar path is not found in PATH.
::    2 if pathVar is missing or undefined or if PATH is undefined.
::
::  If the pathVar path is fully qualified, then it is logically compared
::  to each fully qualified path within PATH. The path strings don't have
::  to match exactly, they just need to be logically equivalent.
::
::  If the pathVar path is relative, then it is strictly compared to each
::  relative path within PATH. Case differences and double quotes are
::  ignored, but otherwise the path strings must match exactly.
::
::------------------------------------------------------------------------
::
:: Error checking
if "%~1"=="" exit /b 2
if not defined %~1 exit /b 2
if not defined path exit /b 2
::
:: Prepare to safely parse PATH into individual paths
setlocal DisableDelayedExpansion
set "var=%path:"=""%"
set "var=%var:^=^^%"
set "var=%var:&=^&%"
set "var=%var:|=^|%"
set "var=%var:<=^<%"
set "var=%var:>=^>%"
set "var=%var:;=^;^;%"
set var=%var:""="%
set "var=%var:"=""Q%"
set "var=%var:;;="S"S%"
set "var=%var:^;^;=;%"
set "var=%var:""="%"
setlocal EnableDelayedExpansion
set "var=!var:"Q=!"
set "var=!var:"S"S=";"!"
::
:: Remove quotes from pathVar and abort if it becomes empty
set "new=!%~1:"=!"
if not defined new exit /b 2
::
:: Determine if pathVar is fully qualified
echo("!new!"|findstr /i /r /c:^"^^\"[a-zA-Z]:[\\/][^\\/]" ^
                           /c:^"^^\"[\\][\\]" >nul ^
  && set "abs=1" || set "abs=0"
::
:: For each path in PATH, check if path is fully qualified and then do
:: proper comparison with pathVar.
:: Exit with ERRORLEVEL 0 if a match is found.
:: Delayed expansion must be disabled when expanding FOR variables
:: just in case the value contains !
for %%A in ("!new!\") do for %%B in ("!var!") do (
  if "!!"=="" endlocal
  for %%C in ("%%~B\") do (
    echo(%%B|findstr /i /r /c:^"^^\"[a-zA-Z]:[\\/][^\\/]" ^
                           /c:^"^^\"[\\][\\]" >nul ^
      && (if %abs%==1 if /i "%%~sA"=="%%~sC" exit /b 0) ^
      || (if %abs%==0 if /i "%%~A"=="%%~C" exit /b 0)
  )
)
:: No match was found so exit with ERRORLEVEL 1
exit /b 1