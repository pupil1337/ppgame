#include "player_air_state.h"

#include <godot_cpp/variant/string_name.hpp>

#include "character/player/state/movement/ground/player_ground_idle_state.h"
#include "character/player/state/movement/ground/player_ground_run_state.h"
#include "character/player/state/player_state_condition.h"

StringName PlayerAirState::on_process(double delta) {
	(void)delta;

	if (condition) {
		// ground state
		// idle
		if (condition->on_ground && condition->input_sign_x == 0 && condition->velocity.x == 0.0) {
			return PlayerGroundIdleState::get_class_static();
		}
		// run
		if (condition->on_ground && (condition->input_sign_x != 0 || condition->velocity.x != 0.0)) {
			return PlayerGroundRunState::get_class_static();
		}
	}

	return StringName();
}
