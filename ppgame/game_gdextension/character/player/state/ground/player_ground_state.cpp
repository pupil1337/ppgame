#include "player_ground_state.h"

#include <godot_cpp/variant/string_name.hpp>

#include "character/player/player.h"
#include "character/player/state/air/player_air_jump_state.h"
#include "character/player/state/player_state_condition.h"

StringName PlayerGroundState::on_physics_process(double delta) {
	if (player && condition) {
		if (condition->pressed_jump && player->is_on_floor()) {
			return PlayerAirJumpState::get_class_static();
		}
	}

	return StringName();
}
