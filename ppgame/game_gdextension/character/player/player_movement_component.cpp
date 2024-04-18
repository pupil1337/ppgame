#include "player_movement_component.h"

#include <cstdint>
#include <godot_cpp/classes/sprite2d.hpp>
#include <godot_cpp/core/defs.hpp>
#include <godot_cpp/core/math.hpp>
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
