#!/bin/bash

GOS_PROJECT_NAME="PID Toolkit"

GOS_CMAKE=cmake
GOS_CTEST=ctest
GOS_QML_PLUGIN_DUMP_EXE=qmlplugindump
GOS_QML_PLUGIN_VERSION=1.0
GOS_QML_PLUGIN=Pid.Toolkit

# Resolve the Current Script Directory
# https://stackoverflow.com/questions/59895/how-to-get-the-source-directory-of-a-bash-script-from-within-the-script-itself
SCRIPT_SOURCE="${BASH_SCRIPT_SOURCE[0]}"
while [ -h "$SCRIPT_SOURCE" ]; do # resolve $SCRIPT_SOURCE until the file is no longer a symlink
  SCRIPT_TARGET="$(readlink "$SCRIPT_SOURCE")"
  if [[ $SCRIPT_TARGET == /* ]]; then
    echo "SCRIPT_SOURCE '$SCRIPT_SOURCE' is an absolute symlink to '$SCRIPT_TARGET'"
    SCRIPT_SOURCE="$SCRIPT_TARGET"
  else
    SCRIPT_DIR="$( dirname "$SCRIPT_SOURCE" )"
    echo "SCRIPT_SOURCE '$SCRIPT_SOURCE' is a relative symlink to '$SCRIPT_TARGET' (relative to '$SCRIPT_DIR')"
    SCRIPT_SOURCE="$SCRIPT_DIR/$SCRIPT_TARGET" # if $SCRIPT_SOURCE was a relative symlink, we need to resolve it relative to the path where the symlink file was located
  fi
done
echo "SCRIPT_SOURCE is '$SCRIPT_SOURCE'"
RSCRIPT_DIR="$( dirname "$SCRIPT_SOURCE" )"
SCRIPT_DIR="$( cd -P "$( dirname "$SCRIPT_SOURCE" )" >/dev/null 2>&1 && pwd )"
if [ "$SCRIPT_DIR" != "$RSCRIPT_DIR" ]; then
  echo "SCRIPT_DIR '$RSCRIPT_DIR' resolves to '$SCRIPT_DIR'"
fi
echo "SCRIPT_DIR is '$SCRIPT_DIR'"

GOS_ROOT_DIR=$SCRIPT_DIR

silent_pushd () {
    command pushd "$@" > /dev/null
}
silent_popd () {
    command popd "$@" > /dev/null
}

echo "---------------------------------------------------------------------------"
echo "Build script for the ${GOS_PROJECT_NAME} project"
echo "${GOS_PROJECT_NAME} root directory is defined as ${GOS_ROOT_DIR}"
