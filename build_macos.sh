#!/bin/bash

BUILD_FOLDER=build_macos
SOURCE_FOLDER=src

echo "==================================="
echo "Super Mario - macOS Build Script"
echo "==================================="
echo ""

# Check if CMake is installed
if ! command -v cmake &> /dev/null
then
    echo "❌ CMake не найден. Пожалуйста, установите CMake:"
    echo "   brew install cmake"
    exit 1
fi

echo "✓ CMake найден: $(cmake --version | head -n 1)"
echo ""

# Create build directory if it doesn't exist
if [ ! -d "$BUILD_FOLDER" ]; then
    echo "Создание директории сборки: $BUILD_FOLDER"
    mkdir "$BUILD_FOLDER"
fi

cd "$BUILD_FOLDER"

echo "Конфигурация проекта с CMake..."
cmake ../"$SOURCE_FOLDER"

if [ $? -ne 0 ]; then
    echo "❌ Ошибка конфигурации CMake"
    cd ..
    exit 1
fi

echo ""
echo "Сборка проекта..."
cmake --build .

if [ $? -ne 0 ]; then
    echo "❌ Ошибка сборки проекта"
    cd ..
    exit 1
fi

cd ..

echo ""
echo "==================================="
echo "✓ Сборка успешно завершена!"
echo "==================================="
echo ""
echo "Запустите игру командой:"
echo "  ./$BUILD_FOLDER/super_mario"
echo ""
echo "Управление:"
echo "  A - движение влево (карта вправо)"
echo "  D - движение вправо (карта влево)"
echo "  Пробел - прыжок"
echo "  ESC - выход"
echo ""
