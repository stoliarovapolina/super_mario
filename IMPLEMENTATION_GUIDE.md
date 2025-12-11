# Руководство по реализации Super Mario

## Обзор проекта

Это объектно-ориентированная версия игры Super Mario, которая демонстрирует следующие принципы проектирования:
1. Отделение логики от визуального представления
2. Независимость от операционной системы
3. Работа с абстракциями вместо конкретных объектов

## Структура проекта

```
src/
├── controller/         # Игровой контроллер
├── levels/            # Уровни игры
├── model/             # Модели данных и интерфейсы
├── objects/           # Игровые объекты (враги, Марио, препятствия)
├── os_controls/       # Управление ОС
└── ui/                # Пользовательский интерфейс
    └── console/       # Консольная реализация UI
```

## Реализованные задачи

### 1. Заполнение уровней объектами

#### Первый уровень (`src/levels/first_level.cpp`)
**Расположение:** `/home/runner/work/super_mario/super_mario/src/levels/first_level.cpp`

Добавлено:
- **12 врагов** (вместо 6) для увеличения сложности
- **10 монет** для сбора игроком
- Дополнительные **коробки** (box) и **полные коробки** (full_box) для создания препятствий

**Концепции C++:**
- Использование метода `init_data()` для инициализации объектов уровня
- Паттерн Factory через `ui_factory->create_*()` методы
- Координаты объектов задаются через структуру `Coord`

#### Второй уровень (`src/levels/second_level.cpp`)
**Расположение:** `/home/runner/work/super_mario/super_mario/src/levels/second_level.cpp`

Добавлено:
- **12 врагов** различных типов
- **8 монет** стратегически размещённых по уровню
- Множество **коробок** и **препятствий** для создания сложных секций
- Обновлён переход на третий уровень (вместо финала)

**Принципы проектирования:**
- Метод `is_final()` изменён на `false` для перехода к следующему уровню
- Метод `get_next()` создаёт экземпляр `ThirdLevel`

---

### 2. Третий уровень игры

#### Файлы:
- **Header:** `src/levels/third_level.hpp`
- **Implementation:** `src/levels/third_level.cpp`

**Описание:**
Финальный уровень игры с максимальной сложностью, включающий все типы врагов.

**Особенности:**
- Использует новые типы врагов: летающих (`FlyingEnemy`) и прыгающих (`JumpingEnemy`)
- Комплексная структура платформ и препятствий
- ~120 объектов (платформы, враги, коробки, монеты)

**Теория C++:**
- Наследование от `GameLevel` (абстрактного базового класса)
- Реализация виртуальных методов: `init_data()`, `get_next()`, `is_final()`
- Метод `is_final()` возвращает `true`, так как это последний уровень

**Паттерны проектирования:**
- **Template Method Pattern**: `GameLevel` определяет структуру, подклассы реализуют детали
- **Chain of Responsibility**: уровни связаны цепочкой через `get_next()`

---

### 3. Летающий враг (Flying Enemy)

#### Файлы модели:
- **Header:** `src/objects/flying_enemy.hpp`
- **Implementation:** `src/objects/flying_enemy.cpp`

#### Файлы UI:
- **Header:** `src/ui/console/ui_objects/console_flying_enemy.hpp`
- **Implementation:** `src/ui/console/ui_objects/console_flying_enemy.cpp`

**Описание:**
Враг, который летает вверх и вниз в определённом диапазоне, двигаясь также горизонтально.

**Реализация:**
```cpp
class FlyingEnemy : public RectMapMovableAdapter, 
                    public Movable, 
                    public Collisionable
```

**Множественное наследование:**
- `RectMapMovableAdapter` - адаптер для движения по карте
- `Movable` - интерфейс подвижных объектов
- `Collisionable` - интерфейс объектов с коллизиями

**Ключевые характеристики:**
- `initial_y` - начальная позиция по Y
- `fly_range` - диапазон полёта (10.0f единиц вверх/вниз)
- `vertical_speed` - скорость вертикального движения (0.15f)

**Поведение:**
1. **Вертикальное движение** (`move_vertically()`):
   - Летает вверх и вниз в диапазоне от `initial_y - fly_range` до `initial_y + fly_range`
   - При достижении границы меняет направление вертикального движения

2. **Горизонтальное движение**:
   - Движется с постоянной скоростью `hspeed = 0.2`
   - При столкновении с препятствием разворачивается

3. **Столкновение с Марио** (`process_mario_collision()`):
   - Убивает Марио при любом столкновении
   - Не может быть убит прыжком сверху (в отличие от обычного врага)

**Визуализация:**
- Символ в консоли: `'F'` (Flying)

**Концепции C++:**
- **Virtual Override**: переопределение метода `move_vertically()` для специального поведения
- **Encapsulation**: приватные поля для состояния полёта

---

### 4. Прыгающий враг (Jumping Enemy)

#### Файлы модели:
- **Header:** `src/objects/jumping_enemy.hpp`
- **Implementation:** `src/objects/jumping_enemy.cpp`

#### Файлы UI:
- **Header:** `src/ui/console/ui_objects/console_jumping_enemy.hpp`
- **Implementation:** `src/ui/console/ui_objects/console_jumping_enemy.cpp`

**Описание:**
Враг, который ходит по земле и периодически прыгает, используя физику гравитации.

**Реализация:**
```cpp
class JumpingEnemy : public RectMapMovableAdapter,
                     public Movable,
                     public Collisionable
```

**Ключевые характеристики:**
- `jump_counter` - счётчик для определения времени прыжка
- `jump_interval` - интервал между прыжками (50 тиков)
- Использует физику гравитации из базового класса `Movable`

**Поведение:**
1. **Вертикальное движение** (`move_vertically()`):
   - Счётчик увеличивается каждый тик
   - Каждые 50 тиков выполняется прыжок (метод `jump()`)
   - Применяется гравитация: `vspeed += V_ACCELERATION`
   - Максимальная скорость падения ограничена `MAX_V_SPEED`

2. **Горизонтальное движение**:
   - Движется с постоянной скоростью `hspeed = 0.15`
   - При столкновении с препятствием разворачивается

3. **Столкновение с Марио** (`process_mario_collision()`):
   - Если Марио падает сверху (`vspeed > 0`), враг умирает
   - В противном случае Марио умирает
   - Аналогично обычному врагу

4. **Вертикальные столкновения** (`process_vertical_static_collision()`):
   - Проверяет, не на краю ли платформы
   - Если на краю - разворачивается
   - При приземлении сбрасывает вертикальную скорость

**Визуализация:**
- Символ в консоли: `'J'` (Jumping)

**Концепции C++:**
- **State Management**: использование `jump_counter` для управления состоянием
- **Physics Simulation**: реалистичная симуляция прыжка и падения
- **Reuse**: использование метода `jump()` из базового класса `Movable`

---

## Архитектура и паттерны проектирования

### 1. Model-View разделение

**Model (Модель):**
- `src/objects/` - логика игровых объектов
- Независима от визуального представления

**View (Представление):**
- `src/ui/console/` - консольная реализация
- Можно добавить другие UI (графический, веб) без изменения модели

### 2. Factory Pattern (Фабрика)

**UIFactory** (`src/model/ui_factory.hpp`):
- Абстрактная фабрика для создания объектов
- Определяет интерфейс: `create_enemy()`, `create_flying_enemy()`, `create_jumping_enemy()` и т.д.

**ConsoleUIFactory** (`src/ui/console/console_ui_factory.hpp`):
- Конкретная реализация фабрики для консольного UI
- Создаёт консольные версии объектов: `ConsoleEnemy`, `ConsoleFlyingEnemy` и т.д.

**Преимущества:**
- Легко добавить новые типы объектов
- Легко создать новую реализацию UI
- Централизованное создание объектов

### 3. Template Method Pattern

**GameLevel** (`src/levels/game_level.hpp`):
- Определяет структуру уровня
- Абстрактный метод `init_data()` реализуется в подклассах
- Общие методы: `restart()`, `is_final()`, `get_next()`

**Конкретные уровни:**
- `FirstLevel`, `SecondLevel`, `ThirdLevel` реализуют `init_data()`
- Каждый уровень определяет свою уникальную расстановку объектов

### 4. Multiple Inheritance (Множественное наследование)

**Пример - Enemy:**
```cpp
class Enemy : public RectMapMovableAdapter,  // Адаптер карты
              public Movable,                 // Движение
              public Collisionable            // Коллизии
```

**Интерфейсы:**
- `Movable` - объекты, которые могут двигаться
- `Collisionable` - объекты, которые могут сталкиваться
- `MapMovable` - объекты, которые реагируют на движение карты

**Виртуальное наследование:**
```cpp
class Movable : virtual public Rect
```
- Решает проблему "diamond problem"
- `Rect` наследуется только один раз

### 5. Adapter Pattern (Адаптер)

**RectMapMovableAdapter** (`src/model/rect_map_movable_adapter.hpp`):
- Адаптирует `Rect` к интерфейсу `MapMovable`
- Позволяет прямоугольным объектам реагировать на движение карты

**ConsoleUIObjectRectAdapter** (`src/ui/console/console_ui_obj_rect_adapter.hpp`):
- Адаптирует игровые объекты к консольному отображению
- Связывает модель с представлением

---

## Методики проектирования и теория C++

### 1. Абстракция

**Принцип:**
Работа с абстракциями вместо конкретных типов.

**Реализация:**
```cpp
class Game {
    std::vector<Movable*> movables;
    std::vector<Collisionable*> collisionables;
    // ...
};
```

- `Game` работает с интерфейсами, а не с конкретными типами
- Можно добавлять новые типы объектов без изменения `Game`

### 2. Инкапсуляция

**Принцип:**
Скрытие внутренней реализации, предоставление публичного интерфейса.

**Примеры:**
```cpp
class FlyingEnemy {
    private:
        float initial_y;        // Скрытое состояние
        float fly_range;
    public:
        void move_vertically(); // Публичный интерфейс
};
```

### 3. Полиморфизм

**Виртуальные функции:**
```cpp
virtual void move_vertically() noexcept;
```

**Переопределение:**
```cpp
void FlyingEnemy::move_vertically() noexcept override {
    // Специфическая реализация для летающего врага
}
```

**Преимущества:**
- Единый интерфейс для разных поведений
- Код вызывающей стороны не зависит от конкретного типа

### 4. SOLID Принципы

**Single Responsibility (Единая ответственность):**
- `Enemy` - логика врага
- `ConsoleEnemy` - отображение врага

**Open/Closed (Открыт для расширения, закрыт для изменения):**
- Новые враги добавляются через наследование
- Базовый код не изменяется

**Liskov Substitution (Подстановка Лисков):**
- `FlyingEnemy` можно использовать везде, где ожидается `Movable`
- `JumpingEnemy` можно использовать везде, где ожидается `Collisionable`

**Interface Segregation (Разделение интерфейсов):**
- `Movable`, `Collisionable`, `MapMovable` - отдельные интерфейсы
- Классы реализуют только нужные интерфейсы

**Dependency Inversion (Инверсия зависимостей):**
- `Game` зависит от абстракций (`Movable`, `Collisionable`)
- Не зависит от конкретных классов (`Enemy`, `FlyingEnemy`)

---

## Система сборки (CMake)

### Обновлённые файлы CMakeLists.txt

**src/objects/CMakeLists.txt:**
```cmake
target_sources(${PROJECT_NAME}
    PRIVATE
        enemy.cpp
        flying_enemy.cpp      # Новый
        jumping_enemy.cpp     # Новый
        # ...
)
```

**src/levels/CMakeLists.txt:**
```cmake
target_sources(${PROJECT_NAME}
    PRIVATE
        first_level.cpp
        second_level.cpp
        third_level.cpp      # Новый
        # ...
)
```

**src/ui/console/ui_objects/CMakeLists.txt:**
```cmake
target_sources(${PROJECT_NAME}
    PRIVATE
        console_enemy.cpp
        console_flying_enemy.cpp      # Новый
        console_jumping_enemy.cpp     # Новый
        # ...
)
```

---

## Как добавить нового врага

### Шаг 1: Создать класс модели

`src/objects/new_enemy.hpp`:
```cpp
#pragma once
#include "collisionable.hpp"
#include "movable.hpp"
#include "rect_map_movable_adapter.hpp"

namespace biv {
    class NewEnemy : public RectMapMovableAdapter,
                     public Movable,
                     public Collisionable {
        public:
            NewEnemy(const Coord& top_left, int width, int height);
            
            // Реализовать необходимые методы
            Rect get_rect() const noexcept override;
            Speed get_speed() const noexcept override;
            void process_mario_collision(Collisionable*) noexcept override;
            // ...
    };
}
```

### Шаг 2: Реализовать логику

`src/objects/new_enemy.cpp`:
```cpp
#include "new_enemy.hpp"

NewEnemy::NewEnemy(const Coord& top_left, int width, int height)
    : RectMapMovableAdapter(top_left, width, height) {
    // Инициализация
}

// Реализация методов...
```

### Шаг 3: Создать консольное представление

`src/ui/console/ui_objects/console_new_enemy.hpp`:
```cpp
#pragma once
#include "console_ui_obj_rect_adapter.hpp"
#include "new_enemy.hpp"

namespace biv {
    class ConsoleNewEnemy : public NewEnemy,
                            public ConsoleUIObjectRectAdapter {
        public:
            ConsoleNewEnemy(const Coord& top_left, int width, int height);
            char get_brush() const noexcept override;
    };
}
```

### Шаг 4: Добавить в фабрику

В `src/model/ui_factory.hpp`:
```cpp
virtual void create_new_enemy(
    const Coord& top_left, int width, int height) = 0;
```

В `src/ui/console/console_ui_factory.hpp` и `.cpp`:
```cpp
void create_new_enemy(
    const Coord& top_left, int width, int height) override;
```

### Шаг 5: Обновить CMakeLists.txt

Добавить файлы в соответствующие `CMakeLists.txt`.

### Шаг 6: Использовать в уровнях

```cpp
ui_factory->create_new_enemy({x, y}, width, height);
```

---

## Игровая механика

### Координатная система

- **Origin (0, 0)** находится в верхнем левом углу
- **X** увеличивается вправо
- **Y** увеличивается вниз

### Физика движения

**Гравитация:**
```cpp
static constexpr float V_ACCELERATION = 0.05f;
static constexpr float MAX_V_SPEED = 0.98f;
```

**Прыжок:**
```cpp
static constexpr float JUMP_SPEED = -1.0f;
```

### Система коллизий

**Типы объектов:**
1. **Static** (статические) - ship, box, full_box
2. **Movable** (подвижные) - mario, enemies
3. **Collisionable** (с коллизиями) - объекты, которые взаимодействуют

**Проверка коллизий:**
- Горизонтальные: `check_horizontally_static_collisions()`
- Вертикальные: `check_vertically_static_collisions()`
- С Марио: `check_mario_collision()`

---

## Изученные концепции C++

### 1. Наследование и полиморфизм
- Одиночное и множественное наследование
- Виртуальные функции и `override`
- Виртуальное наследование (`virtual public`)
- Абстрактные классы и чисто виртуальные функции

### 2. Инкапсуляция
- Модификаторы доступа: `public`, `protected`, `private`
- Геттеры и сеттеры
- Скрытие реализации

### 3. Управление памятью
- `new` и `delete`
- Владение объектами через указатели
- Векторы указателей: `std::vector<Enemy*>`

### 4. Константность
- `const` методы: `get_rect() const noexcept`
- `noexcept` спецификатор
- Константные члены класса

### 5. Структуры данных
- `std::vector` для коллекций объектов
- Структуры (`struct Coord`, `struct Speed`)

### 6. Пространства имён
- `namespace biv` для организации кода
- `using` директивы

### 7. Перечисления
- `enum class` для типобезопасных перечислений

---

## Заключение

Этот проект демонстрирует:
1. **Чистую архитектуру** - разделение ответственности
2. **Паттерны проектирования** - Factory, Template Method, Adapter
3. **SOLID принципы** - расширяемый и поддерживаемый код
4. **Современный C++** - использование возможностей языка

Код легко расширяется новыми уровнями, врагами и визуальными представлениями без изменения существующей логики.
