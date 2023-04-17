#!/bin/sh

ROOT_DIR=$PWD
BUILD_PATH=$ROOT_DIR/build
BUILD_TYPE=Debug

if [ "$1" = "Debug" ]   
then
    BUILD_TYPE=Debug
elif [ "$1" = Release ] 
then
    BUILD_TYPE=Release
fi

BUILD_PATH=$(echo $BUILD_PATH/$BUILD_TYPE | tr '[:upper:]' '[:lower:]')

echo ==============================================================================
echo "BUILD_TYPE: $BUILD_TYPE"
echo "ROOT_DIR:   $ROOT_DIR"
echo "BUILD_PATH: $BUILD_PATH"
echo ==============================================================================

# rm -r "$ROOT_DIR/build" > /dev/null

mkdir -p "$BUILD_PATH"
pushd "$BUILD_PATH/" > /dev/null
	cmake "$ROOT_DIR" -DCMAKE_EXPORT_COMPILE_COMMANDS=1 -DCMAKE_BUILD_TYPE=$BUILD_TYPE -S"$ROOT_DIR" -B"$BUILD_PATH" -G Ninja
	cmake --build . --config $BUILD_TYPE 
popd  > /dev/null
