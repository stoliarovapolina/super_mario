# Сборка и запуск Super Mario на macOS

## Требования

- macOS (любая современная версия)
- CMake (версия 3.2 или выше)
- Компилятор C++ (clang, входит в Xcode Command Line Tools)

## Установка зависимостей

### 1. Установка Xcode Command Line Tools

Если у вас ещё не установлены Xcode Command Line Tools:

```bash
xcode-select --install
```

### 2. Установка CMake

Если CMake не установлен, можно установить через Homebrew:

```bash
# Установка Homebrew (если ещё не установлен)
/bin/bash -c "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/HEAD/install.sh)"

# Установка CMake
brew install cmake
```

## Сборка проекта

### Способ 1: Использование скрипта (рекомендуется)

1. Создайте скрипт сборки для macOS:

```bash
# Создайте файл build_macos.sh
cat > build_macos.sh << 'EOF'
#!/bin/bash

BUILD_FOLDER=build_macos
SOURCE_FOLDER=src

if [ ! -d "$BUILD_FOLDER" ]; then
    mkdir "$BUILD_FOLDER"
fi

cd "$BUILD_FOLDER"

cmake ../"$SOURCE_FOLDER"
cmake --build .

cd ..

echo ""
echo "Сборка завершена! Запустите игру командой:"
echo "./$BUILD_FOLDER/super_mario"
EOF

chmod +x build_macos.sh
```

2. Запустите скрипт:

```bash
./build_macos.sh
```

### Способ 2: Ручная сборка

```bash
# Создание директории для сборки
mkdir -p build_macos
cd build_macos

# Конфигурация проекта
cmake ../src

# Сборка
cmake --build .

# Или используйте make напрямую
make

cd ..
```

## Запуск игры

После успешной сборки запустите игру:

```bash
./build_macos/super_mario
```

## Управление

- **A** - движение влево (карта вправо)
- **D** - движение вправо (карта влево)
- **Пробел** - прыжок
- **ESC** - выход из игры

## Особенности реализации для macOS

Игра использует Unix/POSIX API для работы на macOS:

- **termios** - для настройки терминала (неканонический режим, отключение эха)
- **ANSI escape codes** - для управления курсором и отображением
- **select()** - для неблокирующего чтения ввода с клавиатуры

## Возможные проблемы

### Проблема: Игра не компилируется

**Решение**: Убедитесь, что у вас установлены Xcode Command Line Tools:

```bash
xcode-select --install
```

### Проблема: CMake не найден

**Решение**: Установите CMake через Homebrew:

```bash
brew install cmake
```

### Проблема: Игра отображается некорректно

**Решение**: Используйте стандартный терминал macOS (Terminal.app) или iTerm2. Убедитесь, что размер окна терминала достаточно большой (рекомендуется минимум 80x30).

### Проблема: Игра не реагирует на нажатия клавиш

**Решение**: Убедитесь, что вы запускаете игру в том же терминале, в котором выполняете сборку. Терминал должен иметь фокус ввода.

## Архитектура

Проект использует кросс-платформенную архитектуру:

```
src/os_controls/
├── os_api/          # Общие интерфейсы
├── windows/         # Windows-специфичная реализация
└── unix/            # Unix/macOS-специфичная реализация
```

CMake автоматически выбирает правильную реализацию в зависимости от платформы:
- Windows → компилируется `windows/`
- macOS/Linux → компилируется `unix/`

## Очистка сборки

Для очистки файлов сборки:

```bash
rm -rf build_macos
```

## Дополнительная информация

Для получения дополнительной информации об игре см.:
- **IMPLEMENTATION_GUIDE.md** - подробное руководство по реализации
- **CHANGES.md** - описание изменений
- **SUMMARY.md** - краткое резюме
- **README.md** - общая информация
