#include "player_air_fall_state.h"
#include "character/player/state/air/player_air_state.h"
#include "character/player/state/player_state_condition.h"

#include <godot_cpp/variant/string_name.hpp>

void PlayerAirFallState::enter() {
}

StringName PlayerAirFallState::on_process(double delta) {
	if (condition && !condition->on_ground && !condition->juest_pressed_jump) {
		return StringName();
	}

	return PlayerAirState::on_process(delta);
}

StringName PlayerAirFallState::on_physics_process(double delta) {
	return StringName();
}

void PlayerAirFallState::exit() {
}
