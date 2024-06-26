#include "player_air_fall_state.h"

#include <godot_cpp/core/defs.hpp>
#include <godot_cpp/variant/string_name.hpp>

#include "character/player/player.h"
#include "character/player/player_movement_component.h"
#include "character/player/state/air/player_air_jump_state.h"
#include "character/player/state/player_state_condition.h"
#include "utils/math_utils.h"

void PlayerAirFallState::enter() {
	play_animation("Fall");
}

StringName PlayerAirFallState::on_process(double delta) {
	// jump
	if (condition->just_pressed_jump && condition->can_jump) {
		return PlayerAirJumpState::get_class_static();
	}

	return parent_type::on_process(delta);
}

void PlayerAirFallState::on_physics_process(double delta) {
	if (player && condition) {
		if (PlayerMovementComponent* player_movement_component = player->get_component<PlayerMovementComponent>()) {
			real_t gravity = MathUtils::calculate_fall_gravity(player_movement_component->get_jump_height(), player_movement_component->get_jump_duration(), player_movement_component->get_fall_gravity_multiplayer());
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

void PlayerAirFallState::exit() {
}
