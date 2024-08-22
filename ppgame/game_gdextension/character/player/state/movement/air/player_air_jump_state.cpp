#include "player_air_jump_state.h"

#include <godot_cpp/core/defs.hpp>
#include <godot_cpp/variant/string_name.hpp>
#include <godot_cpp/variant/vector2.hpp>

#include "character/player/player.h"
#include "character/player/player_movement_component.h"
#include "character/player/state/movement/air/player_air_fall_state.h"
#include "character/player/state/player_state_condition.h"
#include "utils/math_utils.h"

void PlayerAirJumpState::enter() {
	desire_jump = true;
	play_animation("Jump");
}

StringName PlayerAirJumpState::on_process(double delta) {
	if (desire_jump) {
		return StringName();
	}

	// fall
	if (!condition->on_ground && condition->velocity.y > 0.0) {
		return PlayerAirFallState::get_class_static();
	}

	return parent_type::on_process(delta);
}

void PlayerAirJumpState::on_physics_process(double delta) {
	if (player && condition) {
		if (PlayerMovementComponent* player_movement_component = player->get_component<PlayerMovementComponent>()) {
			if (desire_jump) {
				player_movement_component->jump(condition->velocity, player_movement_component->get_jump_height(), player_movement_component->get_jump_duration());

				desire_jump = false;
				return;
			}

			real_t gravity = MathUtils::calculate_jump_gravity(player_movement_component->get_jump_height(), player_movement_component->get_jump_duration());
			player_movement_component->input_move(
					delta,
					condition->velocity,
					condition->input_sign_x,
					player_movement_component->get_walk_acceleration(),
					player_movement_component->get_walk_acceleration(),
					player_movement_component->get_walk_turn_speed(),
					player_movement_component->get_walk_max_speed(),
					gravity);
		}
	}
}

void PlayerAirJumpState::exit() {
}
