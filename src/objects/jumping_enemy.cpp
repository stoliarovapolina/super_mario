#include "jumping_enemy.hpp"

#include "map_movable.hpp"

using biv::JumpingEnemy;

JumpingEnemy::JumpingEnemy(const Coord& top_left, const int width, const int height) 
	: RectMapMovableAdapter(top_left, width, height) {
	vspeed = 0;
	hspeed = 0.15;
}

biv::Rect JumpingEnemy::get_rect() const noexcept {
	return {top_left, width, height};
}

biv::Speed JumpingEnemy::get_speed() const noexcept {
	return {vspeed, hspeed};
}

void JumpingEnemy::process_horizontal_static_collision(Rect* obj) noexcept {
	// Разворот при столкновении с препятствием
	hspeed = -hspeed;
	move_horizontally();
}

void JumpingEnemy::process_mario_collision(Collisionable* mario) noexcept {
	// Если Марио падает сверху, враг умирает
	// Иначе Марио умирает
	if (mario->get_speed().v > 0 && mario->get_speed().v != V_ACCELERATION) {
		kill();
	} else {
		mario->kill();
	}
}

void JumpingEnemy::process_vertical_static_collision(Rect* obj) noexcept {
	// Проверка: не свалился ли враг с платформы
	// Если на краю - развернуться
	top_left.x += hspeed;
	if (!has_collision(obj)) {
		process_horizontal_static_collision(obj);
	} else {
		top_left.x -= hspeed;
	}
	
	// Вертикальная механика - остановка при приземлении
	if (vspeed > 0) {
		top_left.y -= vspeed;
		vspeed = 0;
	}
}

void JumpingEnemy::move_vertically() noexcept {
	// Счетчик для прыжков
	jump_counter++;
	
	// Прыжок каждые jump_interval тиков, если на земле
	if (jump_counter >= jump_interval && vspeed == 0) {
		jump();
		jump_counter = 0;
	}
	
	// Применение гравитации
	if (vspeed < MAX_V_SPEED) {
		vspeed += V_ACCELERATION;
	}
	
	// Движение вертикально
	Movable::move_vertically();
}
