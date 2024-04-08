#include "player_movement_component.h"

#include <cstdint>
#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/core/defs.hpp>
#include <godot_cpp/core/math.hpp>
#include <godot_cpp/core/object.hpp>
#include <godot_cpp/core/property_info.hpp>
#include <godot_cpp/variant/utility_functions.hpp>
#include <godot_cpp/variant/variant.hpp>

#include "character/player/player.h"
#include "character/player/player_input_component.h"
#include "framework/actor.h"

void PlayerMovementComponent::_ready() {
	if (actor) {
		player = static_cast<Player*>(actor);
		player_input_component = actor->get_component<PlayerInputComponent>();
	}
}

void PlayerMovementComponent::_process(double delta) {
	if (player_input_component) {
		direct.x = _get_direct(player_input_component->get_motion().x);
		direct.y = _get_direct(player_input_component->get_motion().y);
	}

	// walk input
	desired_walk_velocity = (real_t)direct.x * walk_setting.max_speed;

	// jump input
	if (pressed_jump) {
		if (_can_jump()) {
			desired_jump = true;
			movement_mode = MovementMode::Fall;
		}
		pressed_jump = false;
	}

	// etc...
}

void PlayerMovementComponent::_physics_process(double delta) {
	if (player) {
		velocity = player->get_velocity();

		// physics calculate
		if (movement_mode == MovementMode::Walk) {
			physics_walk(delta);
		} else if (movement_mode == MovementMode::Fall) {
			physics_fall(delta);
		}

		// move
		player->set_velocity(velocity);
		player->move_and_slide();

		// update movement mode
		if (movement_mode == MovementMode::Walk) {
			if (!player->is_on_floor()) {
				movement_mode = MovementMode::Fall;
			}
		} else if (movement_mode == MovementMode::Fall) {
			if (player->is_on_floor()) {
				movement_mode = MovementMode::Walk;
				air_jump_time = 0;
			}
		}
	}
}

// ----------------------------------------------------------------------------
// walk
// ----------------------------------------------------------------------------
void PlayerMovementComponent::physics_walk(double delta) {
	real_t walk_speed_change = 0.0;
	if (direct.x != 0) {
		if (Math::sign(direct.x) != Math::sign(velocity.x)) {
			walk_speed_change = (real_t)walk_setting.turn_speed * delta;
		} else {
			walk_speed_change = (real_t)walk_setting.acceleration * delta;
		}
	} else {
		walk_speed_change = (real_t)walk_setting.deceleration * delta;
	}

	velocity.x = Math::move_toward(velocity.x, desired_walk_velocity, walk_speed_change);
}

// ----------------------------------------------------------------------------
// fall
// ----------------------------------------------------------------------------
void PlayerMovementComponent::jump() {
	pressed_jump = true;
}

void PlayerMovementComponent::stop_jumping() {
	pressed_jump = false;
}

bool PlayerMovementComponent::_can_jump() {
	if (player) {
		if (player->is_on_floor() || air_jump_time < jump_setting.air_jump_time) {
			UtilityFunctions::print("can jump");
			return true;
		}
	}

	UtilityFunctions::print("dont jump");

	return false;
}

void PlayerMovementComponent::_do_jump() {
	desired_jump = false;
	if (player && !player->is_on_floor()) {
		++air_jump_time;
		UtilityFunctions::print("do air jump");
	} else {
		UtilityFunctions::print("do ground jump");
	}

	real_t jump_speed = -2.0 * jump_setting.height / jump_setting.duration;

	velocity.y = jump_speed;
}

void PlayerMovementComponent::physics_fall(double delta) {
	// jump
	if (desired_jump) {
		_do_jump();
		return;
	}

	gravity = 2.0 * jump_setting.height / (jump_setting.duration * jump_setting.duration);

	// falling
	if (velocity.y > 0.01 && player && !player->is_on_floor()) {
		gravity *= jump_setting.fall_gravity_multiplier;
	}

	velocity.y += gravity * delta;
}

// ----------------------------------------------------------------------------
// utils
// ----------------------------------------------------------------------------
int8_t PlayerMovementComponent::_get_direct(real_t p_axis) {
	if (p_axis == 0) {
		return 0;
	} else if (p_axis > 0) {
		return 1;
	} else {
		return -1;
	}
}

void PlayerMovementComponent::set_walk_max_speed(uint32_t p_max_speed) {
	walk_setting.max_speed = p_max_speed;
}

uint32_t PlayerMovementComponent::get_walk_max_speed() {
	return walk_setting.max_speed;
}

void PlayerMovementComponent::set_walk_acceleration(uint32_t p_acceleration) {
	walk_setting.acceleration = p_acceleration;
}

uint32_t PlayerMovementComponent::get_walk_acceleration() {
	return walk_setting.acceleration;
}

void PlayerMovementComponent::set_walk_deceleration(uint32_t p_deceleration) {
	walk_setting.deceleration = p_deceleration;
}

uint32_t PlayerMovementComponent::get_walk_deceleration() {
	return walk_setting.deceleration;
}

void PlayerMovementComponent::set_walk_turn_speed(uint32_t p_turn_speed) {
	walk_setting.turn_speed = p_turn_speed;
}

uint32_t PlayerMovementComponent::get_walk_turn_speed() {
	return walk_setting.turn_speed;
}

void PlayerMovementComponent::set_jump_height(uint32_t p_height) {
	jump_setting.height = p_height;
}

uint32_t PlayerMovementComponent::get_jump_height() {
	return jump_setting.height;
}

void PlayerMovementComponent::set_jump_duration(real_t p_duration) {
	jump_setting.duration = p_duration;
}

real_t PlayerMovementComponent::get_jump_duration() {
	return jump_setting.duration;
}

void PlayerMovementComponent::set_jump_fall_gravity_multiplier(real_t p_fall_gravity_multiplier) {
	jump_setting.fall_gravity_multiplier = p_fall_gravity_multiplier;
}

real_t PlayerMovementComponent::get_jump_fall_gravity_multiplier() {
	return jump_setting.fall_gravity_multiplier;
}

void PlayerMovementComponent::set_jump_air_jump_time(uint8_t p_air_jump_time) {
	jump_setting.air_jump_time = p_air_jump_time;
}

uint8_t PlayerMovementComponent::get_jump_air_jump_time() {
	return jump_setting.air_jump_time;
}

void PlayerMovementComponent::_bind_methods() {
	ADD_GROUP("Walk", "");
	// max_speed
	ClassDB::bind_method(D_METHOD(_STR(set_walk_max_speed), _STR(max_speed)), &self_type::set_walk_max_speed);
	ClassDB::bind_method(D_METHOD(_STR(get_walk_max_speed)), &self_type::get_walk_max_speed);
	ADD_PROPERTY(PropertyInfo(Variant::INT, _STR(max_speed)), _STR(set_walk_max_speed), _STR(get_walk_max_speed));

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

	ADD_GROUP("Jump", "");
	// height
	ClassDB::bind_method(D_METHOD(_STR(set_jump_height), _STR(height)), &self_type::set_jump_height);
	ClassDB::bind_method(D_METHOD(_STR(get_jump_height)), &self_type::get_jump_height);
	ADD_PROPERTY(PropertyInfo(Variant::INT, _STR(jump_height)), _STR(set_jump_height), _STR(get_jump_height));

	// duration
	ClassDB::bind_method(D_METHOD(_STR(set_jump_duration), _STR(duration)), &self_type::set_jump_duration);
	ClassDB::bind_method(D_METHOD(_STR(get_jump_duration)), &self_type::get_jump_duration);
	ADD_PROPERTY(PropertyInfo(Variant::FLOAT, _STR(jump_duration)), _STR(set_jump_duration), _STR(get_jump_duration));

	// fall_gravity_multiplier
	ClassDB::bind_method(D_METHOD(_STR(set_jump_fall_gravity_multiplier), _STR(fall_gravity_multiplier)), &self_type::set_jump_fall_gravity_multiplier);
	ClassDB::bind_method(D_METHOD(_STR(get_jump_fall_gravity_multiplier)), &self_type::get_jump_fall_gravity_multiplier);
	ADD_PROPERTY(PropertyInfo(Variant::FLOAT, _STR(jump_fall_gravity_multiplier)), _STR(set_jump_fall_gravity_multiplier), _STR(get_jump_fall_gravity_multiplier));

	// air_jump_time
	ClassDB::bind_method(D_METHOD(_STR(set_jump_air_jump_time), _STR(air_jump_time)), &self_type::set_jump_air_jump_time);
	ClassDB::bind_method(D_METHOD(_STR(get_jump_air_jump_time)), &self_type::get_jump_air_jump_time);
	ADD_PROPERTY(PropertyInfo(Variant::INT, _STR(jump_air_jump_time)), _STR(set_jump_air_jump_time), _STR(get_jump_air_jump_time));
}
