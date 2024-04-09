#include "player_ground_idle_state.h"

#include <godot_cpp/variant/string_name.hpp>

#include "character/player/state/ground/player_ground_run_state.h"
#include "character/player/state/ground/player_ground_state.h"
#include "character/player/state/player_state_condition.h"

void PlayerGroundIdleState::enter() {
}

StringName PlayerGroundIdleState::on_physics_process(double delta) {
	if (condition && condition->input_motion.x != 0.0) {
		return PlayerGroundRunState::get_class_static();
	}

	return PlayerGroundState::on_physics_process(delta);
}

void PlayerGroundIdleState::exit() {
}
