#include "player_ground_idle_state.h"

#include <godot_cpp/variant/string_name.hpp>

#include "character/player/state/movement/ground/player_ground_run_state.h"
#include "character/player/state/player_state_condition.h"

void PlayerGroundIdleState::enter() {
	play_animation("Idle");
}

StringName PlayerGroundIdleState::on_process(double delta) {
	// run
	if (condition->on_ground && condition->input_sign_x != 0.0) {
		return PlayerGroundRunState::get_class_static();
	}

	return parent_type::on_process(delta);
}

void PlayerGroundIdleState::on_physics_process(double delta) {
}

void PlayerGroundIdleState::exit() {
}
