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

	ui_factory->create_ship({20, 25}, 40, 2);
	ui_factory->create_full_box({25, 17}, 5, 3);
	ui_factory->create_box({35, 17}, 5, 3);
	ui_factory->create_full_box({50, 17}, 5, 3);

	ui_factory->create_ship({70, 20}, 15, 7);
	ui_factory->create_box({70, 12}, 5, 3);
	ui_factory->create_full_box({75, 12}, 5, 3);
	ui_factory->create_money({73, 7}, 2, 2);

	ui_factory->create_flying_enemy({73, 5}, 3, 2);

	ui_factory->create_ship({95, 25}, 25, 2);
	ui_factory->create_box({100, 17}, 5, 3);
	ui_factory->create_full_box({110, 17}, 5, 3);
	ui_factory->create_money({95, 18}, 2, 2);
	ui_factory->create_money({105, 12}, 2, 2);
	ui_factory->create_money({115, 18}, 2, 2);

	ui_factory->create_box({125, 22}, 5, 3);
	ui_factory->create_full_box({135, 18}, 5, 3);
	ui_factory->create_box({145, 14}, 5, 3);
	ui_factory->create_money({130, 15}, 2, 2);
	ui_factory->create_money({140, 11}, 2, 2);

	ui_factory->create_ship({155, 20}, 15, 7);
	ui_factory->create_full_box({157, 12}, 5, 3);
	ui_factory->create_box({165, 12}, 5, 3);
	ui_factory->create_money({160, 7}, 2, 2);

	ui_factory->create_flying_enemy({160, 9}, 3, 2);

	
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


	ui_factory->create_full_box({252, 12}, 5, 3);
	ui_factory->create_box({257, 12}, 5, 3);

	ui_factory->create_ship({250, 20}, 15, 7);

	ui_factory->create_finish({250, 20}, 10, 10);
}