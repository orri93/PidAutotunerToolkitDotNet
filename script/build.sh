#!/bin/bash

GOS_PROJECT_NAME="PID Toolkit"

GOS_CMAKE=cmake
GOS_CTEST=ctest
GOS_QML_PLUGIN_DUMP_EXE=qmlplugindump
GOS_QML_PLUGIN_VERSION=1.0
GOS_QML_PLUGIN=Pid.Toolkit

# Resolve the Current Script Directory
CURRENT_SCRIPT_SOURCE="${BASH_CURRENT_SCRIPT_SOURCE[0]}"
# resolve $CURRENT_SCRIPT_SOURCE until the file is no longer a symlink
while [ -h "$CURRENT_SCRIPT_SOURCE" ]; do
  $CURRENT_SCRIPT_DIR="$( cd -P "$( dirname "$CURRENT_SCRIPT_SOURCE" )" >/dev/null && pwd )"
  CURRENT_SCRIPT_SOURCE="$(readlink "$CURRENT_SCRIPT_SOURCE")"
  [[ $CURRENT_SCRIPT_SOURCE != /* ]] && CURRENT_SCRIPT_SOURCE="$DIR/$CURRENT_SCRIPT_SOURCE" # if $CURRENT_SCRIPT_SOURCE was a relative symlink, we need to resolve it relative to the path where the symlink file was located
done
#$CURRENT_SCRIPT_DIR="$( cd -P "$( dirname "$CURRENT_SCRIPT_SOURCE" )" >/dev/null && pwd )"
GOS_ROOT_DIR=${$CURRENT_SCRIPT_DIR}

silent_pushd () {
    command pushd "$@" > /dev/null
}
silent_popd () {
    command popd "$@" > /dev/null
}

echo "---------------------------------------------------------------------------"
echo "Build script for the ${GOS_PROJECT_NAME} project"
echo "${GOS_PROJECT_NAME} root directory is defined as ${GOS_ROOT_DIR}"
