#include "player_air_jump_state.h"

#include <godot_cpp/core/defs.hpp>
#include <godot_cpp/variant/string_name.hpp>
#include <godot_cpp/variant/vector2.hpp>

#include "character/player/player.h"
#include "character/player/state/air/player_air_fall_state.h"
#include "character/player/state/air/player_air_state.h"
#include "character/player/state/player_state_condition.h"
#include "utils/math_utils.h"

void PlayerAirJumpState::enter() {
	desire_jump = true;
}

StringName PlayerAirJumpState::on_process(double delta) {
	// TODO 删除PlayerAirJumpDashState例子
	// if (condition->can_jump /* can jump dash */) {
	// 	return PlayerAirJumpDashState::get_class_static();
	// }
	// end

	if (desire_jump) {
		return StringName();
	}

	// fall
	if (!condition->on_ground && condition->velocity.y > 0.0) {
		return PlayerAirFallState::get_class_static();
	}

	return PlayerAirState::on_process(delta);
}

void PlayerAirJumpState::on_physics_process(double delta) {
	if (player && condition) {
		if (desire_jump) {
			Vector2 new_velocity = condition->velocity;
			new_velocity.y = Utils::calculate_jump_speed_y(96.0, 0.4);
			player->set_velocity(new_velocity);
			player->move_and_slide();

			desire_jump = false;
			return;
		}

		real_t gravity = Utils::calculate_jump_gravity(96.0, 0.4);
		Vector2 new_velocity = Utils::air_move(delta, condition->input_sign_x, condition->velocity, gravity);
		player->set_velocity(new_velocity);
		player->move_and_slide();
	}
}

void PlayerAirJumpState::exit() {
}
