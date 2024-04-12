#include "player_ground_run_state.h"

#include <godot_cpp/variant/string_name.hpp>
#include <godot_cpp/variant/vector2.hpp>

#include "character/player/player.h"
#include "character/player/state/ground/player_ground_idle_state.h"
#include "character/player/state/player_state_condition.h"
#include "utils/math_utils.h"

void PlayerGroundRunState::enter() {
}

StringName PlayerGroundRunState::on_process(double delta) {
	// idle
	if (condition->on_ground && condition->input_sign_x == 0 && condition->velocity.x == 0.0) {
		return PlayerGroundIdleState::get_class_static();
	}

	return super::on_process(delta);
}

void PlayerGroundRunState::on_physics_process(double delta) {
	if (player && condition) {
		Vector2 new_velocity = MathUtils::input_move(
				delta,
				condition->velocity,
				condition->input_sign_x,
				600.0,
				5000.0,
				1200.0,
				0.0,
				400.0);
		player->set_velocity(new_velocity);
		player->move_and_slide();
	}
}

void PlayerGroundRunState::exit() {
}
