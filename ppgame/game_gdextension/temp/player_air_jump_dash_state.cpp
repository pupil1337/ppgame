#include "player_air_jump_dash_state.h"
#include "character/player/state/air/player_air_jump_state.h"
#include "character/player/state/player_state.h"
#include "character/player/state/player_state_condition.h"
#include "godot_cpp/variant/string_name.hpp"

void PlayerAirJumpDashState::enter() {
}

StringName PlayerAirJumpDashState::on_process(double delta) {
	if (condition->juest_pressed_jump /* jump dash again*/) {
		// jump_dash again ...
		return StringName();
	}

	// if jump dash end
	return PlayerAirJumpState::on_process(delta);
}

void PlayerAirJumpDashState::on_physics_process(double delta) {
}

void PlayerAirJumpDashState::exit() {
}
