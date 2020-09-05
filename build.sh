#!/bin/sh

set -x

SOURCE_DIR=`pwd`
BUILD_DIR=${BUILD_DIR:-./build}
BUILD_TYPE=${BUILD_TYPE:-release}
CXX=${CXX:-g++}

mkdir -p $BUILD_DIR \
  && cd $BUILD_DIR \
  && cmake .. \
  && make $*


