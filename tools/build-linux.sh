#!/bin/sh

LOCAL=$PWD
NAME=
BUILD_MODE=debug
BUILD_DIR=$LOCAL/build
CODE_DIR=$LOCAL/code
EXTERNAL_DIR=$LOCAL/external
FLAGS="-Wall -Werror -Wextra -Wno-unused-parameter -Wno-unused-function -Wno-unused-parameter -Wno-unused-variable -Wno-unused-but-set-variable -Wno-unused-but-set-parameter"

if [ "$1" = debug ] 
then 
    BUILD_MODE=$1 
    FLAGS="$FLAGS -O0 -g -DENABLE_ASSERT"

elif [ "$1" = release ] 
then
    BUILD_MODE=$1 
    FLAGS="$FLAGS -O3"
elif [ "$1" = "" ]
then
    FLAGS="$FLAGS -O0 -g -DENABLE_ASSERT"
fi

BUILD_DIR=$BUILD_DIR/$BUILD_MODE
mkdir -p $LOCAL/build
mkdir -p $LOCAL/build/$BUILD_MODE
 
NAME=tnt
#echo "NAME:       "$NAME""
#echo "BUILD_MODE: "$BUILD_MODE""
#echo "FLAGS:      "$FLAGS""
#echo "BUILD_DIR:  "$BUILD_DIR""
pushd "$BUILD_DIR/" > /dev/null
    clang $FLAGS -m64 \
    -lm -lX11 -lGL \
    -L"$BUILD_DIR" \
    -I"$CODE_DIR" \
    -I"$EXTERNAL_DIR/glad/include" \
    "$CODE_DIR/tnt.c" \
    -o "$NAME"
popd > /dev/null
