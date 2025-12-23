#!/bin/bash

BUILD_FOLDER=build
SOURCE_FOLDER=src

if ! command -v cmake &> /dev/null; then
    echo "CMake не найден. Установите: brew install cmake"
    exit 1
fi

if [ ! -d "$BUILD_FOLDER" ]; then
    mkdir "$BUILD_FOLDER"
fi

cd "$BUILD_FOLDER"
cmake ../"$SOURCE_FOLDER" && cmake --build .
cd ..