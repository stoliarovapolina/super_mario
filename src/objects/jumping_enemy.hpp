#pragma once

#include "collisionable.hpp"
#include "movable.hpp"
#include "rect.hpp"
#include "rect_map_movable_adapter.hpp"
#include "speed.hpp"

namespace biv {
	/**
	 * Прыгающий враг - враг, который ходит по земле и периодически прыгает.
	 * Использует механику гравитации и прыжков.
	 */
	class JumpingEnemy : public RectMapMovableAdapter, public Movable, public Collisionable {
		private:
			int jump_counter = 0;      // Счетчик для определения времени прыжка
			int jump_interval = 50;    // Интервал между прыжками (в тиках)
			
		public:
			JumpingEnemy(const Coord& top_left, const int width, const int height);

			Rect get_rect() const noexcept override;
			Speed get_speed() const noexcept override;

			void process_horizontal_static_collision(Rect*) noexcept override;
			void process_mario_collision(Collisionable*) noexcept override;
			void process_vertical_static_collision(Rect*) noexcept override;
			
			void move_vertically() noexcept override;
	};
}
