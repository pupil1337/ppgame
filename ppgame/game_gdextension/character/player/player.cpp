#include "player.h"

#include <cstdint>
#include <godot_cpp/classes/area2d.hpp>
#include <godot_cpp/classes/collision_shape2d.hpp>
#include <godot_cpp/variant/vector2.hpp>

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

void Player::face_to_input(int8_t p_input_sign_x) {
	parent_type::face_to_input(p_input_sign_x);

	if (p_input_sign_x != 0) {
		if (Area2D* melee_attack_area = get_melee_attack_area()) {
			melee_attack_area->set_scale(get_scale() * Vector2(p_input_sign_x, 1.0));
		}
	}
}

// ----------------------------------------------------------------------------

Area2D* Player::get_melee_attack_area() {
	return get_node<Area2D>("MeleeAttackArea");
}

CollisionShape2D* Player::get_melee_attack_shape() {
	return get_node<CollisionShape2D>("MeleeAttackArea/CollisionShape2D");
}
