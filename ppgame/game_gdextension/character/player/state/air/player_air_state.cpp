#include "player_air_state.h"

#include <godot_cpp/variant/string_name.hpp>

void PlayerAirState::enter() {
}

StringName PlayerAirState::on_physics_process(double delta) {
	return StringName();
}

void PlayerAirState::exit() {
}
