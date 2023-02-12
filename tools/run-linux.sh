#!/bin/sh

LOCAL=$PWD
NAME=$1
BUILD_MODE=debug
BUILD_DIR=$LOCAL/build

if [[ "$1" = "" || "$2" = "" ]]; then echo "Error arguments"; exit; fi

if [ "$2" = debug ] 
then 
    BUILD_MODE=$2
    BUILD_DIR="$BUILD_DIR/$2"
elif [ "$2" = release ] 
then
    BUILD_MODE=$2
    BUILD_DIR="$BUILD_DIR/$2"
else
    echo "No found build mode: $2"
    exit
fi

echo "NAME:       $NAME"
echo "BUILD_MODE: $BUILD_MODE"
echo "BUILD_DIR:  $BUILD_DIR"

pushd "$BUILD_DIR/" > /dev/null
    ./$NAME
popd > /dev/null