#include "player_ground_run_state.h"

#include <godot_cpp/variant/string_name.hpp>
#include <godot_cpp/variant/vector2.hpp>

#include "character/player/player.h"
#include "character/player/player_movement_component.h"
#include "character/player/state/movement/ground/player_ground_idle_state.h"
#include "character/player/state/player_state_condition.h"

void PlayerGroundRunState::enter() {
	play_animation("Run");
}

StringName PlayerGroundRunState::on_process(double delta) {
	// idle
	if (condition->on_ground && condition->input_sign_x == 0 && condition->velocity.x == 0.0) {
		return PlayerGroundIdleState::get_class_static();
	}

	return parent_type::on_process(delta);
}

void PlayerGroundRunState::on_physics_process(double delta) {
	if (player && condition) {
		if (PlayerMovementComponent* player_movement_component = player->get_component<PlayerMovementComponent>()) {
			player_movement_component->input_move(delta,
					condition->velocity,
					condition->input_sign_x,
					player_movement_component->get_walk_acceleration(),
					player_movement_component->get_walk_deceleration(),
					player_movement_component->get_walk_turn_speed(),
					player_movement_component->get_walk_max_speed(),
					0.0);
		}
	}
}

void PlayerGroundRunState::exit() {
}
