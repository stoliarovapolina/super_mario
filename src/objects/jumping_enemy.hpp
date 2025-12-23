#pragma once

#include "enemy.hpp"

namespace biv {
	class JumpingEnemy : public Enemy {
		private:
			float jump_hspeed = 0.25f; // горизонтальная скорость во время прыжка
			int jump_cooldown = 0;
			static constexpr int JUMP_COOLDOWN_TICKS = 25;

		public:
			JumpingEnemy(const Coord& top_left, const int width, const int height);

			void process_vertical_static_collision(Rect* platform) noexcept override;

		private:
			float predict_jump_dx() const noexcept;
			bool will_land_on_platform(Rect* platform, float dx) const noexcept;
	};
}