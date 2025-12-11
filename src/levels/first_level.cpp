#include "first_level.hpp"

#include "second_level.hpp"

using biv::FirstLevel;

FirstLevel::FirstLevel(UIFactory* ui_factory) : GameLevel(ui_factory) {
	init_data();
}

biv::GameLevel* FirstLevel::get_next() {
	if (!next) {
		clear_data();
		next = new biv::SecondLevel(ui_factory);
	}
	return next;
}

// ----------------------------------------------------------------------------
// 									PROTECTED
// ----------------------------------------------------------------------------
void FirstLevel::init_data() {
	ui_factory->create_mario({39, 10}, 3, 3);
	
	// Первая платформа с объектами
	ui_factory->create_ship({20, 25}, 40, 2);
	ui_factory->create_money({35, 15}, 2, 2);
	ui_factory->create_money({45, 15}, 2, 2);
	
	// Коробки в воздухе
	ui_factory->create_full_box({30, 15}, 5, 3);
	ui_factory->create_full_box({50, 15}, 5, 3);
	ui_factory->create_money({40, 10}, 2, 2);
	
	// Большая платформа с препятствиями
	ui_factory->create_ship({60, 20}, 40, 7);
	
	ui_factory->create_box({60, 10}, 10, 3);
	ui_factory->create_full_box({70, 10}, 5, 3);
	ui_factory->create_box({75, 10}, 5, 3);
	ui_factory->create_full_box({80, 10}, 5, 3);
	ui_factory->create_box({85, 10}, 10, 3);
	
	// Монеты над препятствиями
	ui_factory->create_money({65, 5}, 2, 2);
	ui_factory->create_money({72, 5}, 2, 2);
	ui_factory->create_money({78, 5}, 2, 2);
	ui_factory->create_money({90, 5}, 2, 2);
	
	// Средние платформы
	ui_factory->create_ship({100, 25}, 20, 2);
	ui_factory->create_ship({120, 20}, 10, 7);
	ui_factory->create_money({105, 18}, 2, 2);
	ui_factory->create_money({115, 18}, 2, 2);
	ui_factory->create_full_box({125, 12}, 5, 3);
	
	// Длинная платформа с монетами
	ui_factory->create_ship({150, 25}, 40, 2);
	ui_factory->create_money({155, 18}, 2, 2);
	ui_factory->create_money({165, 18}, 2, 2);
	ui_factory->create_money({175, 18}, 2, 2);
	ui_factory->create_money({185, 18}, 2, 2);
	
	// Финальная платформа
	ui_factory->create_ship({210, 20}, 15, 7);
	ui_factory->create_full_box({215, 12}, 5, 3);
	
	// Враги (добавлено больше врагов для сложности)
	ui_factory->create_enemy({20, 5}, 3, 2);
	ui_factory->create_enemy({25, 5}, 3, 2);
	ui_factory->create_enemy({35, 5}, 3, 2);
	ui_factory->create_enemy({70, 15}, 3, 2);
	ui_factory->create_enemy({80, 5}, 3, 2);
	ui_factory->create_enemy({90, 15}, 3, 2);
	ui_factory->create_enemy({105, 5}, 3, 2);
	ui_factory->create_enemy({125, 5}, 3, 2);
	ui_factory->create_enemy({155, 5}, 3, 2);
	ui_factory->create_enemy({160, 5}, 3, 2);
	ui_factory->create_enemy({175, 5}, 3, 2);
	ui_factory->create_enemy({215, 5}, 3, 2);
}
