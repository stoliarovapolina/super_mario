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
	// Марио в той же позиции
	ui_factory->create_mario({39, 10}, 3, 3);
	
	// Платформы (BRICK -> SHIP)
	ui_factory->create_ship({20, 20}, 40, 5);      // bricks[0]
	ui_factory->create_ship({60, 15}, 40, 10);     // bricks[3]
	ui_factory->create_ship({100, 20}, 20, 5);     // bricks[9]
	ui_factory->create_ship({120, 15}, 10, 10);    // bricks[10]
	ui_factory->create_ship({150, 20}, 40, 5);     // bricks[11]
	ui_factory->create_ship({210, 15}, 10, 10);    // bricks[12] WIN_BRICK
	
	// Коробки в воздухе
	ui_factory->create_full_box({30, 10}, 5, 3);   // bricks[1]
	ui_factory->create_full_box({50, 10}, 5, 3);   // bricks[2]
	ui_factory->create_box({60, 5}, 10, 3);        // bricks[4]
	ui_factory->create_full_box({70, 5}, 5, 3);    // bricks[5]
	ui_factory->create_box({75, 5}, 5, 3);         // bricks[6]
	ui_factory->create_full_box({80, 5}, 5, 3);    // bricks[7]
	ui_factory->create_box({85, 5}, 10, 3);        // bricks[8]
	
	// Враги (ENEMY)
	ui_factory->create_enemy({25, 10}, 3, 2);      // movings[0]
	ui_factory->create_enemy({80, 10}, 3, 2);      // movings[1]

	ui_factory->create_jumping_enemy({170,19}, 3, 2);
	
	ui_factory->create_ship({210, 20}, 15, 7);
	ui_factory->create_finish({210, 15}, 15, 15);
}