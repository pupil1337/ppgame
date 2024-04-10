#include "player_ground_run_state.h"

#include <godot_cpp/variant/string_name.hpp>

#include "character/player/player.h"
#include "character/player/state/ground/player_ground_state.h"
#include "character/player/state/player_state_condition.h"
#include "godot_cpp/variant/vector2.hpp"
#include "utils/math_utils.h"

void PlayerGroundRunState::enter() {
}

StringName PlayerGroundRunState::on_process(double delta) {
	if (condition && condition->on_ground && condition->velocity.x != 0.0) {
		return StringName();
	}

	return PlayerGroundState::on_process(delta);
}

StringName PlayerGroundRunState::on_physics_process(double delta) {
	if (player && condition) {
		Vector2 new_velocity = Utils::ground_move(delta, condition->input_sign_x, condition->velocity, 400.0, 600.0, 5000.0, 1200.0);
		player->set_velocity(new_velocity);
		player->move_and_slide();
	}

	return StringName();
}

void PlayerGroundRunState::exit() {
}
