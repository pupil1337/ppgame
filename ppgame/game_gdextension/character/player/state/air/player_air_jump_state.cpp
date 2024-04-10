#include "player_air_jump_state.h"
#include "character/player/state/air/player_air_state.h"

#include <godot_cpp/variant/string_name.hpp>

void PlayerAirJumpState::enter() {
}

StringName PlayerAirJumpState::on_process(double delta) {
	return PlayerAirState::on_process(delta);
}

StringName PlayerAirJumpState::on_physics_process(double delta) {
	return PlayerAirState::on_physics_process(delta);
}

void PlayerAirJumpState::exit() {
}
