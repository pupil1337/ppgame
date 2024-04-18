#include "player_ground_run_state.h"

#include <godot_cpp/classes/animation_player.hpp>
#include <godot_cpp/variant/string_name.hpp>
#include <godot_cpp/variant/vector2.hpp>

#include "character/player/player.h"
#include "character/player/player_movement_component.h"
#include "character/player/state/ground/player_ground_idle_state.h"
#include "character/player/state/player_state_condition.h"

void PlayerGroundRunState::enter() {
	if (player) {
		if (AnimationPlayer* animation_player = player->get_animation_player()) {
			animation_player->play("Run");
		}
	}
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
		if (PlayerMovementComponent* player_movement_component = player->get_component<PlayerMovementComponent>()) {
			player_movement_component->input_move(delta,
					condition->velocity,
					condition->input_sign_x,
					600.0,
					5000.0,
					1200.0,
					400.0,
					0.0);
		}
	}
}

void PlayerGroundRunState::exit() {
}
