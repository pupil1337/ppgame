#include "player_air_fall_state.h"

#include <godot_cpp/variant/string_name.hpp>

void PlayerAirFallState::enter() {
}

StringName PlayerAirFallState::on_physics_process(double delta) {
	return StringName();
}

void PlayerAirFallState::exit() {
}
