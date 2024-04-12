#include "player_air_fall_state.h"

#include <godot_cpp/core/defs.hpp>
#include <godot_cpp/variant/string_name.hpp>

#include "character/player/player.h"
#include "character/player/state/air/player_air_jump_state.h"
#include "character/player/state/player_state_condition.h"
#include "utils/math_utils.h"

void PlayerAirFallState::enter() {
}

StringName PlayerAirFallState::on_process(double delta) {
	// jump
	if (condition->just_pressed_jump && condition->can_jump) {
		return PlayerAirJumpState::get_class_static();
	}

	return super::on_process(delta);
}

void PlayerAirFallState::on_physics_process(double delta) {
	if (player && condition) {
		real_t gravity = MathUtils::calculate_fall_gravity(96.0, 0.4, 2.0);
		Vector2 new_velocity = MathUtils::input_move(
				delta,
				condition->velocity,
				condition->input_sign_x,
				600.0,
				600.0,
				1800.0,
				gravity,
				400.0);
		player->set_velocity(new_velocity);
		player->move_and_slide();
	}
}

void PlayerAirFallState::exit() {
}
