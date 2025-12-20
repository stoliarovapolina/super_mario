#include "flying_enemy.hpp"

#include "map_movable.hpp"

using biv::FlyingEnemy;

FlyingEnemy::FlyingEnemy(const Coord& top_left, const int width, const int height) 
	: RectMapMovableAdapter(top_left, width, height) {
	initial_y = top_left.y;
	vspeed = vertical_speed;
	hspeed = 0.2;
}

biv::Rect FlyingEnemy::get_rect() const noexcept {
	return {top_left, width, height};
}

biv::Speed FlyingEnemy::get_speed() const noexcept {
	return {vspeed, hspeed};
}

void FlyingEnemy::process_horizontal_static_collision(Rect* obj) noexcept {
	
	hspeed = -hspeed;
	move_horizontally();
}

void FlyingEnemy::process_mario_collision(Collisionable* mario) noexcept {
	
	mario->kill();
}

void FlyingEnemy::process_vertical_static_collision(Rect* obj) noexcept {

}

void FlyingEnemy::move_vertically() noexcept {
	
	if ((top_left.y >= initial_y + fly_range && vspeed > 0) ||
	    (top_left.y <= initial_y - fly_range && vspeed < 0)) {
		vspeed = -vspeed;
	}
	
	top_left.y += vspeed;
}
