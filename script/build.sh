#!/bin/bash

GOS_PROJECT_NAME="PID Toolkit"

GOS_CMAKE=cmake
GOS_CTEST=ctest
GOS_QML_PLUGIN_DUMP_EXE=qmlplugindump
GOS_QML_PLUGIN_VERSION=1.0
GOS_QML_PLUGIN=Pid.Toolkit

die() {
  printf '%s\n' "$1" >&2
  exit 1
}

GOS_BUILD_NUMBER=0
GOS_BUILD_DOCS=ON

# http://mywiki.wooledge.org/BashFAQ/035
while :; do
  case $1 in
    -h|-\?|--help)
      show_help      # Display a usage synopsis.
      exit
      ;;
    -nc|--no-clean|--not--clean)
      echo "Not Clean detected"
      GOS_NOT_CLEAN=NOT_CLEAN
      ;;
    -nb|--no-build|--not-build)
      GOS_NOT_BUILD=NOT_BUILD
      ;;
    -nd|--no_doc|--not-doc|--no_docs|--not-docs)
      GOS_BUILD_DOCS=OFF
      ;;
    -n|--build-number)
      GOS_BUILD_NUMBER=$2
      ;;
    --)              # End of all options.
      shift
      break
      ;;
    -?*)
      printf 'WARN: Unknown option (ignored): %s\n' "$1" >&2
      ;;
    *)               # Default case: No more options, so break out of the loop.
      break
  esac
  shift
done

# Resolve the Current Script Directory
# https://stackoverflow.com/questions/59895/how-to-get-the-source-directory-of-a-bash-script-from-within-the-script-itself
#!/bin/bash

SOURCE="${BASH_SOURCE[0]}"
while [ -h "$SOURCE" ]; do # resolve $SOURCE until the file is no longer a symlink
  TARGET="$(readlink "$SOURCE")"
  if [[ $TARGET == /* ]]; then
    echo "SOURCE '$SOURCE' is an absolute symlink to '$TARGET'"
    SOURCE="$TARGET"
  else
    DIR="$( dirname "$SOURCE" )"
    echo "SOURCE '$SOURCE' is a relative symlink to '$TARGET' (relative to '$DIR')"
    SOURCE="$DIR/$TARGET" # if $SOURCE was a relative symlink, we need to resolve it relative to the path where the symlink file was located
  fi
done
echo "SOURCE is '$SOURCE'"
RDIR="$( dirname "$SOURCE" )"
DIR="$( cd -P "$( dirname "$SOURCE" )" >/dev/null 2>&1 && pwd )"
if [ "$DIR" != "$RDIR" ]; then
  echo "DIR '$RDIR' resolves to '$DIR'"
fi
echo "DIR is '$DIR'"

# Silent pushd and popd
silent_pushd () {
    command pushd "$@" > /dev/null
}
silent_popd () {
    command popd "$@" > /dev/null
}


GOS_ROOT_DIR=`realpath "$DIR/.."`

echo "---------------------------------------------------------------------------"
echo "Build script for the ${GOS_PROJECT_NAME} project"
echo "${GOS_PROJECT_NAME} root directory is defined as ${GOS_ROOT_DIR}"

GOS_BUILD_CONFIG=release

GOS_PROJECT_BUILD_DIR=${GOS_ROOT_DIR}/build/${GOS_BUILD_CONFIG}
GOS_PROJECT_ARTIFACTS_DIR=${GOS_ROOT_DIR}/artifacts/${GOS_BUILD_CONFIG}
GOS_PROJECT_INCLUDE_DIR=${GOS_ROOT_DIR}/include

GOS_CMAKE_SYSTEM=Ninja
#GOS_CMAKE_PLATFORM=

#--log-level=DEBUG \
#-DGOS_DEPLOY_PDB_FILES:BOOL=ON \
#-DGOS_PID_TOOLKIT_UI_PLUGIN_GENERATE_DUMMY:BOOL=ON \
#-DDOXYGEN_DIA_EXECUTABLE:FILEPATH="%GOS_DIA_EXE_PATH%" \
#-A %GOS_CMAKE_PLATFORM% "%GOS_ROOT_DIR%"
GOS_CMAKE_CREATE_OPTIONS=\
--graphviz="${GOS_PROJECT_ARTIFACTS_DIR}/share/graphviz/pidtoolkit" \
-DBUILD_DOCS:BOOL=${GOS_BUILD_DOCS} \
-DCMAKE_INSTALL_PREFIX:PATH="${GOS_PROJECT_ARTIFACTS_DIR}" \
-DCMAKE_BUILD_TYPE=${GOS_BUILD_CONFIG} \
-G "${GOS_CMAKE_SYSTEM}"

echo "- GOS Build number is defined as ${GOS_BUILD_NUMBER}"
echo "- Install path is defined as ${GOS_PROJECT_ARTIFACTS_DIR}"
echo "- CMake buld system is defined as ${GOS_CMAKE_SYSTEM}"
echo "- CMake buld platform is defined as ${GOS_CMAKE_PLATFORM}"
echo "- CMake buld directory is defined as ${GOS_PROJECT_BUILD_DIR}"
echo "- CMake buld configuration is defined as ${GOS_BUILD_CONFIG}"

GOS_CMAKE_BUILD_OPTIONS=--build "${GOS_PROJECT_BUILD_DIR}" --target all --config ${GOS_BUILD_CONFIG}
GOS_CMAKE_INSTALL_OPTIONS=--build "${GOS_PROJECT_BUILD_DIR}" --target install --config ${GOS_BUILD_CONFIG}
GOS_CMAKE_DOXYGEN_OPTIONS=--build "${GOS_PROJECT_BUILD_DIR}" --target doxygetpidtoolkit --config ${GOS_BUILD_CONFIG}
GOS_CTEST_OPTIONS=--build-config ${GOS_BUILD_CONFIG}



if [ $GOS_NOT_CLEAN = "NOT_CLEAN" ]; then
  echo "Skipping Clean"
else
  echo "*** Clean"
  if [ -d "$DIRECTORY" ]; then
    echo "The build folder already exists so deleting the old"
    "${GOS_CMAKE}" -E remove_directory "${GOS_PROJECT_BUILD_DIR}"
  fi
fi
