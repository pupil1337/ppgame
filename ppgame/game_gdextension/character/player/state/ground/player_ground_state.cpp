#include "player_ground_state.h"

#include <godot_cpp/variant/string_name.hpp>

#include "character/player/state/air/player_air_fall_state.h"
#include "character/player/state/air/player_air_jump_state.h"
#include "character/player/state/player_state_condition.h"

StringName PlayerGroundState::on_process(double delta) {
	if (condition) {
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
