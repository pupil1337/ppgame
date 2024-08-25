#include "player.h"

#include <godot_cpp/classes/animation_player.hpp>
#include <godot_cpp/classes/collision_shape2d.hpp>
#include <godot_cpp/classes/sprite2d.hpp>

void Player::_enter_tree() {
	parent_type::_enter_tree();
}

void Player::_ready() {
	parent_type::_ready();
}

void Player::_process(double delta) {
	parent_type::_process(delta);
}

void Player::_physics_process(double delta) {
	parent_type::_physics_process(delta);
}

void Player::_exit_tree() {
	parent_type::_exit_tree();
}

Sprite2D* Player::get_sprite() {
	return get_node<Sprite2D>("Sprite2D");
}

AnimationPlayer* Player::get_animation_player() {
	return get_node<AnimationPlayer>("AnimationPlayer");
}

CollisionShape2D* Player::get_collision_shape() {
	return get_node<CollisionShape2D>("CollisionShape2D");
}
