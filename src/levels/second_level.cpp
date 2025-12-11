#include "second_level.hpp"

#include "third_level.hpp"

using biv::SecondLevel;

SecondLevel::SecondLevel(UIFactory* ui_factory) : GameLevel(ui_factory) {
	init_data();
}

bool SecondLevel::is_final() const noexcept {
	return false;
}

biv::GameLevel* SecondLevel::get_next() {
	if (!next) {
		clear_data();
		next = new biv::ThirdLevel(ui_factory);
	}
	return next;
}

// ----------------------------------------------------------------------------
// 									PROTECTED
// ----------------------------------------------------------------------------
void SecondLevel::init_data() {
	ui_factory->create_mario({39, 10}, 3, 3);
	
	// Стартовая платформа с препятствиями
	ui_factory->create_ship({20, 25}, 40, 2);
	ui_factory->create_full_box({25, 17}, 5, 3);
	ui_factory->create_box({35, 17}, 5, 3);
	ui_factory->create_full_box({45, 17}, 5, 3);
	ui_factory->create_money({30, 12}, 2, 2);
	ui_factory->create_money({50, 12}, 2, 2);
	
	// Высокая платформа
	ui_factory->create_ship({60, 20}, 10, 7);
	ui_factory->create_box({60, 12}, 5, 3);
	ui_factory->create_money({63, 7}, 2, 2);
	
	// Средняя платформа
	ui_factory->create_ship({80, 25}, 20, 2);
	ui_factory->create_full_box({85, 17}, 5, 3);
	ui_factory->create_money({82, 18}, 2, 2);
	ui_factory->create_money({95, 18}, 2, 2);
	
	// Сложная секция с коробками
	ui_factory->create_box({105, 22}, 5, 3);
	ui_factory->create_full_box({110, 18}, 5, 3);
	ui_factory->create_box({115, 14}, 5, 3);
	
	// Еще одна высокая платформа
	ui_factory->create_ship({120, 20}, 10, 7);
	ui_factory->create_full_box({122, 12}, 5, 3);
	ui_factory->create_money({125, 7}, 2, 2);
	
	// Платформа с монетами
	ui_factory->create_ship({150, 25}, 40, 2);
	ui_factory->create_money({155, 18}, 2, 2);
	ui_factory->create_money({165, 18}, 2, 2);
	ui_factory->create_money({175, 18}, 2, 2);
	ui_factory->create_money({185, 18}, 2, 2);
	ui_factory->create_box({160, 17}, 5, 3);
	ui_factory->create_full_box({170, 17}, 5, 3);
	ui_factory->create_box({180, 17}, 5, 3);
	
	// Финальная сложная платформа
	ui_factory->create_ship({210, 20}, 10, 7);
	ui_factory->create_full_box({210, 12}, 5, 3);
	ui_factory->create_box({215, 12}, 5, 3);
	ui_factory->create_money({213, 7}, 2, 2);
	
	// Враги (второй уровень сложнее)
	ui_factory->create_enemy({25, 5}, 3, 2);
	ui_factory->create_enemy({35, 5}, 3, 2);
	ui_factory->create_enemy({50, 5}, 3, 2);
	ui_factory->create_enemy({63, 5}, 3, 2);
	ui_factory->create_enemy({85, 5}, 3, 2);
	ui_factory->create_enemy({95, 5}, 3, 2);
	ui_factory->create_enemy({125, 5}, 3, 2);
	ui_factory->create_enemy({155, 5}, 3, 2);
	ui_factory->create_enemy({165, 5}, 3, 2);
	ui_factory->create_enemy({175, 5}, 3, 2);
	ui_factory->create_enemy({185, 5}, 3, 2);
	ui_factory->create_enemy({213, 5}, 3, 2);
}
