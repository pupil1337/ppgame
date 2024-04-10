#include "player_ground_state.h"

#include <godot_cpp/variant/string_name.hpp>

#include "character/player/state/air/player_air_fall_state.h"
#include "character/player/state/air/player_air_jump_state.h"
#include "character/player/state/ground/player_ground_idle_state.h"
#include "character/player/state/ground/player_ground_run_state.h"
#include "character/player/state/player_state_condition.h"

StringName PlayerGroundState::on_process(double delta) {
	if (condition) {
		// ground state
		// idle
		if (condition->on_ground && condition->velocity.x == 0.0) {
			return PlayerGroundIdleState::get_class_static();
		}
		// run
		if (condition->on_ground && condition->velocity.x != 0.0) {
			return PlayerGroundRunState::get_class_static();
		}

		// air state
		// jump
		if (condition->juest_pressed_jump && condition->can_jump) {
			return PlayerAirJumpState::get_class_static();
		}
		// fall
		if (!condition->on_ground) {
			return PlayerAirFallState::get_class_static();
		}
	}

	return StringName();
}

StringName PlayerGroundState::on_physics_process(double delta) {
	return StringName();
}
