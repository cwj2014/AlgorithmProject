#!/bin/sh

dir=build
if [ -d $dir ]; then
  echo "clear build directory"
  rm -rf $dir
fi
mkdir $dir
cd $dir
cmake -DCMAKE_BUILD_TYPE=$1 ..
make

