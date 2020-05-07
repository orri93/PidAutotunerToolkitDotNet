@ECHO OFF

SETLOCAL ENABLEEXTENSIONS

SET GOS_ROOT_DIR=..
CALL:MakeAbsolute GOS_ROOT_DIR "%~dp0"

SET GOS_PROJECT_NAME=PID Toolkit
SET GOS_CMAKE_EXE=cmake

ECHO ---------------------------------------------------------------------------

ECHO Clean the %GOS_PROJECT_NAME% project

ECHO %GOS_PROJECT_NAME% root directory is defined as %GOS_ROOT_DIR%

SET GOS_PROJECT_SRC_DIR=%GOS_ROOT_DIR%\src\cpp
SET GOS_PROJECT_PID_TOOLKIT_UI_DIR=%GOS_PROJECT_SRC_DIR%\pidtoolkitui
SET GOS_PROJECT_PID_TOOLKIT_UI_QT_DEBUG_DIR=%GOS_PROJECT_PID_TOOLKIT_UI_DIR%\debug
SET GOS_PROJECT_PID_TOOLKIT_UI_QT_RELEASE_DIR=%GOS_PROJECT_PID_TOOLKIT_UI_DIR%\release

ECHO PID Toolkit UI source directory is defined as %GOS_PROJECT_PID_TOOLKIT_UI_DIR%

SET GOS_PROJECT_OUT_DIR=%GOS_ROOT_DIR%\out
SET GOS_PROJECT_BUILD_DIR=%GOS_ROOT_DIR%\build

REM IF EXIST "%GOS_PROJECT_OUT_DIR%" (
REM  ECHO The VS out folder exists so deleting
REM  "%GOS_CMAKE_EXE%" -E remove_directory "%GOS_PROJECT_OUT_DIR%"
REM )

REM CALL:gos_delete_folder_if_exists %GOS_PROJECT_OUT_DIR%

CALL:gos_delete_folder_if_exists %GOS_PROJECT_BUILD_DIR%

CALL:gos_delete_folder_if_exists %GOS_PROJECT_PID_TOOLKIT_UI_QT_DEBUG_DIR%

CALL:gos_delete_folder_if_exists %GOS_PROJECT_PID_TOOLKIT_UI_QT_RELEASE_DIR%

CALL:gos_delete_file_if_exists %GOS_PROJECT_PID_TOOLKIT_UI_DIR%\.qmake.stash

CALL:gos_delete_file_if_exists %GOS_PROJECT_PID_TOOLKIT_UI_DIR%\Makefile

CALL:gos_delete_file_if_exists %GOS_PROJECT_PID_TOOLKIT_UI_DIR%\Makefile.Debug

CALL:gos_delete_file_if_exists %GOS_PROJECT_PID_TOOLKIT_UI_DIR%\Makefile.Release


REM Done
GOTO:EOF

:gos_delete_folder_if_exists folder
IF EXIST %~1 GOTO gos_delete_folder_exists
ECHO Folder %~1 doesn't exists
GOTO gos_delete_folder_done
:gos_delete_folder_exists
ECHO Folder %~1 exists so deleting with CMake
"%GOS_CMAKE_EXE%" -E remove_directory %~1
:gos_delete_folder_done
EXIT /b

:gos_delete_file_if_exists file
IF EXIST "%~1" GOTO gos_delete_file_exists
ECHO File %~1 doesn't exists
GOTO gos_delete_file_done
:gos_delete_file_exists
ECHO File %~1 exists so deleting
DEL "%~1"
:gos_delete_file_done
EXIT /b


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