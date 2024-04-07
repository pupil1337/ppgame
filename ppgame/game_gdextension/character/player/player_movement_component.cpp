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
		direct_x = _get_direct(player_input_component->get_motion().x);
	}

	desired_velocity.x = (real_t)direct_x * max_speed;
}

void PlayerMovementComponent::_physics_process(double delta) {
	if (player) {
		velocity = player->get_velocity();

		if (direct_x != 0) {
			if (Math::sign(direct_x) != Math::sign(velocity.x)) {
				speed_change = (real_t)turn_speed * delta;
			} else {
				speed_change = (real_t)acceleration * delta;
			}
		} else {
			speed_change = (real_t)deceleration * delta;
		}

		velocity.x = Math::move_toward(velocity.x, desired_velocity.x, speed_change);

		player->set_velocity(velocity);
		player->move_and_slide();
	}
}

int8_t PlayerMovementComponent::_get_direct(real_t p_axis) {
	if (p_axis == 0) {
		return 0;
	} else if (p_axis > 0) {
		return 1;
	} else {
		return -1;
	}
}

void PlayerMovementComponent::set_max_speed(uint32_t p_max_speed) {
	max_speed = p_max_speed;
}

uint32_t PlayerMovementComponent::get_max_speed() {
	return max_speed;
}

void PlayerMovementComponent::set_acceleration(uint32_t p_acceleration) {
	acceleration = p_acceleration;
}

uint32_t PlayerMovementComponent::get_acceleration() {
	return acceleration;
}

void PlayerMovementComponent::set_deceleration(uint32_t p_deceleration) {
	deceleration = p_deceleration;
}

uint32_t PlayerMovementComponent::get_deceleration() {
	return deceleration;
}

void PlayerMovementComponent::set_turn_speed(uint32_t p_turn_speed) {
	turn_speed = p_turn_speed;
}

uint32_t PlayerMovementComponent::get_turn_speed() {
	return turn_speed;
}

void PlayerMovementComponent::_bind_methods() {
	// max_speed
	ClassDB::bind_method(D_METHOD(_STR(set_max_speed), _STR(max_speed)), &self_type::set_max_speed);
	ClassDB::bind_method(D_METHOD(_STR(get_max_speed)), &self_type::get_max_speed);
	ADD_PROPERTY(PropertyInfo(Variant::INT, _STR(max_speed)), _STR(set_max_speed), _STR(get_max_speed));

	// acceleration
	ClassDB::bind_method(D_METHOD(_STR(set_acceleration), _STR(acceleration)), &self_type::set_acceleration);
	ClassDB::bind_method(D_METHOD(_STR(get_acceleration)), &self_type::get_acceleration);
	ADD_PROPERTY(PropertyInfo(Variant::INT, _STR(acceleration)), _STR(set_acceleration), _STR(get_acceleration));

	// deceleration
	ClassDB::bind_method(D_METHOD(_STR(set_deceleration), _STR(deceleration)), &self_type::set_deceleration);
	ClassDB::bind_method(D_METHOD(_STR(get_deceleration)), &self_type::get_deceleration);
	ADD_PROPERTY(PropertyInfo(Variant::INT, _STR(deceleration)), _STR(set_deceleration), _STR(get_deceleration));

	// turn_speed
	ClassDB::bind_method(D_METHOD(_STR(set_turn_speed), _STR(turn_speed)), &self_type::set_turn_speed);
	ClassDB::bind_method(D_METHOD(_STR(get_turn_speed)), &self_type::get_turn_speed);
	ADD_PROPERTY(PropertyInfo(Variant::INT, _STR(turn_speed)), _STR(set_turn_speed), _STR(get_turn_speed));
}
