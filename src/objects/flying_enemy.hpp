#pragma once

#include "collisionable.hpp"
#include "movable.hpp"
#include "rect.hpp"
#include "rect_map_movable_adapter.hpp"
#include "speed.hpp"

namespace biv {
	/**
	 * Летающий враг - враг, который двигается горизонтально и вертикально.
	 * Летает вверх и вниз в определенном диапазоне.
	 */
	class FlyingEnemy : public RectMapMovableAdapter, public Movable, public Collisionable {
		private:
			float initial_y;           // Начальная позиция по Y
			float fly_range = 10.0f;   // Диапазон полета вверх/вниз
			float vertical_speed = 0.15f;  // Скорость вертикального движения
			
		public:
			FlyingEnemy(const Coord& top_left, const int width, const int height);

			Rect get_rect() const noexcept override;
			Speed get_speed() const noexcept override;

			void process_horizontal_static_collision(Rect*) noexcept override;
			void process_mario_collision(Collisionable*) noexcept override;
			void process_vertical_static_collision(Rect*) noexcept override;
			
			void move_vertically() noexcept override;
	};
}
