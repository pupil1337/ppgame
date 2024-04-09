#include "player_air_jump_state.h"

#include <godot_cpp/variant/string_name.hpp>

void PlayerAirJumpState::enter() {
}

StringName PlayerAirJumpState::on_physics_process(double delta) {
	return StringName();
}

void PlayerAirJumpState::exit() {
}
