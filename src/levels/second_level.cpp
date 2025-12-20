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
	// Марио в той же позиции
	ui_factory->create_mario({39, 10}, 3, 3);
	

	ui_factory->create_ship({20, 20}, 40, 5);      // bricks[0]
	ui_factory->create_ship({60, 15}, 10, 10);     // bricks[1]
	ui_factory->create_ship({80, 20}, 20, 5);      // bricks[2]
	ui_factory->create_ship({120, 15}, 10, 10);    // bricks[3]
	ui_factory->create_ship({150, 20}, 40, 5);     // bricks[4]
	ui_factory->create_ship({210, 15}, 10, 10);    // bricks[5] WIN_BRICK
	

	ui_factory->create_enemy({25, 10}, 3, 2);      // movings[0]
	ui_factory->create_enemy({80, 10}, 3, 2);      // movings[1]
	ui_factory->create_enemy({65, 10}, 3, 2);      // movings[2]
	ui_factory->create_enemy({120, 10}, 3, 2);     // movings[3]
	ui_factory->create_enemy({160, 10}, 3, 2);     // movings[4]
	ui_factory->create_enemy({175, 10}, 3, 2);     // movings[5]

	ui_factory->create_ship({210, 20}, 10, 7);
	ui_factory->create_finish({210, 15}, 10, 10);
	
}