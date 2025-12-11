#include "third_level.hpp"

using biv::ThirdLevel;

ThirdLevel::ThirdLevel(UIFactory* ui_factory) : GameLevel(ui_factory) {
	init_data();
}

bool ThirdLevel::is_final() const noexcept {
	return true;
}

biv::GameLevel* ThirdLevel::get_next() {
	return next;
}

// ----------------------------------------------------------------------------
// 									PROTECTED
// ----------------------------------------------------------------------------
void ThirdLevel::init_data() {
	ui_factory->create_mario({39, 10}, 3, 3);
	
	// Начальная секция - знакомство с новыми врагами
	ui_factory->create_ship({20, 25}, 40, 2);
	ui_factory->create_full_box({25, 17}, 5, 3);
	ui_factory->create_box({35, 17}, 5, 3);
	ui_factory->create_full_box({50, 17}, 5, 3);
	ui_factory->create_money({30, 12}, 2, 2);
	ui_factory->create_money({45, 12}, 2, 2);
	
	// Первый прыгающий враг
	ui_factory->create_jumping_enemy({25, 5}, 3, 2);
	ui_factory->create_jumping_enemy({40, 5}, 3, 2);
	
	// Первый летающий враг
	ui_factory->create_flying_enemy({55, 15}, 3, 2);
	
	// Высокая секция с комбинацией врагов
	ui_factory->create_ship({70, 20}, 15, 7);
	ui_factory->create_box({70, 12}, 5, 3);
	ui_factory->create_full_box({75, 12}, 5, 3);
	ui_factory->create_money({73, 7}, 2, 2);
	ui_factory->create_enemy({73, 5}, 3, 2);
	ui_factory->create_flying_enemy({80, 15}, 3, 2);
	
	// Средняя сложная секция
	ui_factory->create_ship({95, 25}, 25, 2);
	ui_factory->create_box({100, 17}, 5, 3);
	ui_factory->create_full_box({110, 17}, 5, 3);
	ui_factory->create_money({95, 18}, 2, 2);
	ui_factory->create_money({105, 12}, 2, 2);
	ui_factory->create_money({115, 18}, 2, 2);
	ui_factory->create_jumping_enemy({98, 5}, 3, 2);
	ui_factory->create_enemy({108, 5}, 3, 2);
	ui_factory->create_flying_enemy({115, 15}, 3, 2);
	
	// Сложная воздушная секция с коробками
	ui_factory->create_box({125, 22}, 5, 3);
	ui_factory->create_full_box({135, 18}, 5, 3);
	ui_factory->create_box({145, 14}, 5, 3);
	ui_factory->create_money({130, 15}, 2, 2);
	ui_factory->create_money({140, 11}, 2, 2);
	ui_factory->create_flying_enemy({130, 20}, 3, 2);
	ui_factory->create_flying_enemy({140, 16}, 3, 2);
	
	// Высокая платформа с врагами
	ui_factory->create_ship({155, 20}, 15, 7);
	ui_factory->create_full_box({157, 12}, 5, 3);
	ui_factory->create_box({165, 12}, 5, 3);
	ui_factory->create_money({160, 7}, 2, 2);
	ui_factory->create_jumping_enemy({157, 5}, 3, 2);
	ui_factory->create_enemy({165, 5}, 3, 2);
	ui_factory->create_flying_enemy({175, 15}, 3, 2);
	
	// Длинная финальная платформа с множеством врагов
	ui_factory->create_ship({185, 25}, 50, 2);
	ui_factory->create_full_box({190, 17}, 5, 3);
	ui_factory->create_box({200, 17}, 5, 3);
	ui_factory->create_full_box({210, 17}, 5, 3);
	ui_factory->create_box({220, 17}, 5, 3);
	
	ui_factory->create_money({185, 18}, 2, 2);
	ui_factory->create_money({195, 12}, 2, 2);
	ui_factory->create_money({205, 12}, 2, 2);
	ui_factory->create_money({215, 12}, 2, 2);
	ui_factory->create_money({225, 18}, 2, 2);
	
	// Финальная секция со всеми типами врагов
	ui_factory->create_enemy({188, 5}, 3, 2);
	ui_factory->create_jumping_enemy({195, 5}, 3, 2);
	ui_factory->create_enemy({202, 5}, 3, 2);
	ui_factory->create_jumping_enemy({210, 5}, 3, 2);
	ui_factory->create_enemy({218, 5}, 3, 2);
	ui_factory->create_jumping_enemy({225, 5}, 3, 2);
	
	ui_factory->create_flying_enemy({192, 15}, 3, 2);
	ui_factory->create_flying_enemy({208, 15}, 3, 2);
	ui_factory->create_flying_enemy({222, 15}, 3, 2);
	
	// Финальная высокая платформа
	ui_factory->create_ship({250, 20}, 15, 7);
	ui_factory->create_full_box({252, 12}, 5, 3);
	ui_factory->create_box({257, 12}, 5, 3);
	ui_factory->create_money({255, 7}, 2, 2);
	ui_factory->create_flying_enemy({255, 15}, 3, 2);
	ui_factory->create_jumping_enemy({252, 5}, 3, 2);
}
