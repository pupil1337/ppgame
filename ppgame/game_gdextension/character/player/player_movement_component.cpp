#include "player_movement_component.h"

#include <cstdint>
#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/core/defs.hpp>
#include <godot_cpp/core/math.hpp>
#include <godot_cpp/core/object.hpp>
#include <godot_cpp/core/property_info.hpp>
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
			}
		}
	}
}

// ----------------------------------------------------------------------------
// walk
// ----------------------------------------------------------------------------
void PlayerMovementComponent::physics_walk(double delta) {
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
		return player->is_on_floor();
	}

	return false;
}

void PlayerMovementComponent::_do_jump() {
	desired_jump = false;

	velocity.y += 30 * -9.8;
}

void PlayerMovementComponent::_calculate_gravity() {
	gravity_multiplier = 1.0;
}

void PlayerMovementComponent::physics_fall(double delta) {
	if (desired_jump) {
		_do_jump();
	}

	_calculate_gravity();

	velocity.y += gravity_multiplier * 9.8;
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

void PlayerMovementComponent::_bind_methods() {
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
}
