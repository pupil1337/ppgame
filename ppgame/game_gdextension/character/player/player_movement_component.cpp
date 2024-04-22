#include "player_movement_component.h"

#include <cstdint>
#include <godot_cpp/classes/sprite2d.hpp>
#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/core/defs.hpp>
#include <godot_cpp/core/math.hpp>
#include <godot_cpp/core/object.hpp>
#include <godot_cpp/core/property_info.hpp>
#include <godot_cpp/variant/variant.hpp>
#include <godot_cpp/variant/vector2.hpp>

#include "character/player/player.h"

void PlayerMovementComponent::_ready() {
	super::_ready();

	if (actor) {
		player = static_cast<Player*>(actor);
		player_sprite = player->get_sprite();
	}
}

void PlayerMovementComponent::input_move(double delta, Vector2 curr_velocity, int8_t input_sign_x, real_t acceleration_x, real_t deceleration_x, real_t turn_speed_x, real_t max_speed_x, real_t gravity) {
	// x
	real_t speed_change_x = 0.0;
	if (input_sign_x != 0) {
		if (Math::sign(input_sign_x) != Math::sign(curr_velocity.x)) {
			speed_change_x = turn_speed_x * delta;
		} else {
			speed_change_x = acceleration_x * delta;
		}
	} else {
		speed_change_x = deceleration_x * delta;
	}
	real_t new_velocity_x = Math::move_toward(curr_velocity.x, input_sign_x * max_speed_x, speed_change_x);

	// y
	real_t new_velocity_y = curr_velocity.y + gravity * delta;

	// sprite_face_to_input
	if (sprite_face_to_input && input_sign_x != 0) {
		if (player_sprite) {
			player_sprite->set_flip_h(input_sign_x < 0);
		}
	}

	// move
	if (player) {
		player->set_velocity({ new_velocity_x, new_velocity_y });
		player->move_and_slide();
	}
}

real_t PlayerMovementComponent::get_walk_acceleration() {
	return walk_setting.acceleration;
}

real_t PlayerMovementComponent::get_walk_deceleration() {
	return walk_setting.deceleration;
}

real_t PlayerMovementComponent::get_walk_turn_speed() {
	return walk_setting.turn_speed;
}

real_t PlayerMovementComponent::get_walk_max_speed() {
	return walk_setting.max_speed;
}

real_t PlayerMovementComponent::get_jump_height() {
	return jump_setting.height;
}

real_t PlayerMovementComponent::get_jump_duration() {
	return jump_setting.duration;
}

real_t PlayerMovementComponent::get_fall_gravity_multiplayer() {
	return fall_setting.gravity_multiplayer;
}

// ----------------------------------------------------------------------------

void PlayerMovementComponent::set_walk_acceleration(real_t p_acceleration) {
	walk_setting.acceleration = p_acceleration;
}

void PlayerMovementComponent::set_walk_deceleration(real_t p_deceleration) {
	walk_setting.deceleration = p_deceleration;
}

void PlayerMovementComponent::set_walk_turn_speed(real_t p_turn_speed) {
	walk_setting.turn_speed = p_turn_speed;
}

void PlayerMovementComponent::set_walk_max_speed(real_t p_max_speed) {
	walk_setting.max_speed = p_max_speed;
}

void PlayerMovementComponent::set_jump_height(real_t p_height) {
	jump_setting.height = p_height;
}

void PlayerMovementComponent::set_jump_duration(real_t p_duration) {
	jump_setting.duration = p_duration;
}

void PlayerMovementComponent::set_fall_gravity_multiplayer(real_t p_multiplayer) {
	fall_setting.gravity_multiplayer = p_multiplayer;
}

void PlayerMovementComponent::_bind_methods() {
	ADD_GROUP("walk", "");
	{
		// acceleration
		ClassDB::bind_method(D_METHOD(_STR(set_walk_acceleration), _STR(acceleration)), &self_type::set_walk_acceleration);
		ClassDB::bind_method(D_METHOD(_STR(get_walk_acceleration)), &self_type::get_walk_acceleration);
		ADD_PROPERTY(PropertyInfo(Variant::INT, _STR(acceleration)), _STR(set_walk_acceleration), _STR(get_walk_acceleration));

		// deceleration
		ClassDB::bind_method(D_METHOD(_STR(set_walk_deceleration), _STR(deceleration)), &self_type::set_walk_deceleration);
		ClassDB::bind_method(D_METHOD(_STR(get_walk_deceleration)), &self_type::get_walk_deceleration);
		ADD_PROPERTY(PropertyInfo(Variant::INT, _STR(deceleration)), _STR(set_walk_deceleration), _STR(get_walk_deceleration));

		// turn_speed
		ClassDB::bind_method(D_METHOD(_STR(set_walk_turn_speed), _STR(turn_speed)), &self_type::set_walk_turn_speed);
		ClassDB::bind_method(D_METHOD(_STR(get_walk_turn_speed)), &self_type::get_walk_turn_speed);
		ADD_PROPERTY(PropertyInfo(Variant::INT, _STR(turn_speed)), _STR(set_walk_turn_speed), _STR(get_walk_turn_speed));

		// max_speed
		ClassDB::bind_method(D_METHOD(_STR(set_walk_max_speed), _STR(max_speed)), &self_type::set_walk_max_speed);
		ClassDB::bind_method(D_METHOD(_STR(get_walk_max_speed)), &self_type::get_walk_max_speed);
		ADD_PROPERTY(PropertyInfo(Variant::INT, _STR(max_speed)), _STR(set_walk_max_speed), _STR(get_walk_max_speed));
	}

	ADD_GROUP("jump", "");
	{
		// height
		ClassDB::bind_method(D_METHOD(_STR(set_jump_height), _STR(height)), &self_type::set_jump_height);
		ClassDB::bind_method(D_METHOD(_STR(get_jump_height)), &self_type::get_jump_height);
		ADD_PROPERTY(PropertyInfo(Variant::INT, _STR(height)), _STR(set_jump_height), _STR(get_jump_height));

		// duration
		ClassDB::bind_method(D_METHOD(_STR(set_jump_duration), _STR(duration)), &self_type::set_jump_duration);
		ClassDB::bind_method(D_METHOD(_STR(get_jump_duration)), &self_type::get_jump_duration);
		ADD_PROPERTY(PropertyInfo(Variant::FLOAT, _STR(duration)), _STR(set_jump_duration), _STR(get_jump_duration));
	}

	ADD_GROUP("fall", "");
	{
		// gravity_multiplayer
		ClassDB::bind_method(D_METHOD(_STR(set_fall_gravity_multiplayer), _STR(multiplayer)), &self_type::set_fall_gravity_multiplayer);
		ClassDB::bind_method(D_METHOD(_STR(get_fall_gravity_multiplayer)), &self_type::get_fall_gravity_multiplayer);
		ADD_PROPERTY(PropertyInfo(Variant::FLOAT, _STR(gravity_multiplayer)), _STR(set_fall_gravity_multiplayer), _STR(get_fall_gravity_multiplayer));
	}
}
