#include "player_air_jump_state.h"
#include "character/player/player.h"
#include "character/player/state/air/player_air_fall_state.h"
#include "character/player/state/air/player_air_state.h"
#include "character/player/state/player_state_condition.h"
#include "godot_cpp/core/defs.hpp"
#include "godot_cpp/variant/vector2.hpp"
#include "utils/math_utils.h"

#include <godot_cpp/variant/string_name.hpp>

void PlayerAirJumpState::enter() {
	jump_count = 0;
}

StringName PlayerAirJumpState::on_process(double delta) {
	// TODO 删除PlayerAirJumpDashState例子
	// if (condition->can_jump /* can jump dash */) {
	// 	return PlayerAirJumpDashState::get_class_static();
	// }
	// end

	// fall
	if (!condition->on_ground && condition->velocity.y > 0.0) {
		return PlayerAirFallState::get_class_static();
	}

	return PlayerAirState::on_process(delta);
}

void PlayerAirJumpState::on_physics_process(double delta) {
	if (player && condition) {
		if (jump_count == 0) {
			Vector2 new_velocity = condition->velocity;
			new_velocity.y = Utils::calculate_jump_speed_y(96.0, 0.4);
			player->set_velocity(new_velocity);
			player->move_and_slide();

			++jump_count;
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
