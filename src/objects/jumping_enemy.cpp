#include "jumping_enemy.hpp"

using biv::JumpingEnemy;

JumpingEnemy::JumpingEnemy(const Coord& top_left, const int width, const int height)
	: Enemy(top_left, width, height) {
	// он не "ходит" как обычный Enemy
	hspeed = 0.0f;
	vspeed = 0.0f;

	// направление по умолчанию
	jump_hspeed = 0.25f;
	jump_cooldown = 10;
}

// Симулируем прыжок по вертикали и считаем, сколько тиков он будет в воздухе.
// Затем dx = hspeed * ticks.
float JumpingEnemy::predict_jump_dx() const noexcept {
	// берём параметры из Movable
	const float JUMP_SPEED = -1.0f;
	const float V_ACCELERATION = 0.05f;
	const float MAX_V_SPEED = 0.98f;

	float v = JUMP_SPEED;
	int ticks = 0;

	// Считаем, когда он "вернётся" к платформе.
	// Условие приземления в нашей простой симуляции:
	// как только после некоторого времени вертикальная скорость стала >= 0
	// и мы "условно" пролетели вниз столько же, сколько вверх.
	// Для простоты считаем до момента, когда v станет >= MAX_V_SPEED или ticks лимит.
	float y = 0.0f;
	const int MAX_TICKS = 200;

	while (ticks < MAX_TICKS) {
		// шаг физики как в Movable::move_vertically()
		if (v < MAX_V_SPEED) v += V_ACCELERATION;
		y += v;
		ticks++;

		// y >= 0 означает "вернулись" примерно на уровень старта
		if (ticks > 1 && y >= 0.0f) {
			break;
		}
	}

	return jump_hspeed * static_cast<float>(ticks);
}

// Проверяем, что после прыжка "опорная точка" (центр снизу) окажется над платформой.
// То есть: X центра должен лежать внутри [platform.left, platform.right).
bool JumpingEnemy::will_land_on_platform(Rect* platform, float dx) const noexcept {
	const float future_center_x = (top_left.x + dx) + width * 0.5f;

	// небольшой eps, чтобы не залипать на границе
	const float eps = 0.01f;

	return future_center_x > platform->get_left() + eps
		&& future_center_x < platform->get_right() - eps;
}

void JumpingEnemy::process_vertical_static_collision(Rect* platform) noexcept {
	// приземление (как минимум)
	if (vspeed > 0) {
		top_left.y -= vspeed;
		vspeed = 0;
	}

	// на земле стоит
	hspeed = 0.0f;

	if (jump_cooldown > 0) {
		--jump_cooldown;
		return;
	}

	// 1) предсказываем дальность прыжка
	const float dx = predict_jump_dx();

	// 2) проверяем — приземлится ли на платформу
	if (!will_land_on_platform(platform, dx)) {
		// разворот и повторная проверка
		jump_hspeed = -jump_hspeed;
		const float dx2 = predict_jump_dx();

		if (!will_land_on_platform(platform, dx2)) {
			// с обеих сторон нет безопасного приземления
			jump_cooldown = JUMP_COOLDOWN_TICKS;
			return;
		}
	}

	// 3) запускаем прыжок и даём горизонтальную скорость на время прыжка
	hspeed = jump_hspeed;
	jump();

	jump_cooldown = JUMP_COOLDOWN_TICKS;
}