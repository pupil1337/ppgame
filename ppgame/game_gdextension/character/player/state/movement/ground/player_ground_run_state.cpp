#include "player_ground_run_state.h"

#include <godot_cpp/variant/string_name.hpp>
#include <godot_cpp/variant/vector2.hpp>

#include "character/character_movement_component.h"
#include "character/player/player.h"
#include "character/player/state/movement/ground/player_ground_idle_state.h"
#include "character/player/state/player_state_condition.h"

void PlayerGroundRunState::enter() {
	if (animation_player && condition && !condition->ban_movement_enter_anim) {
		animation_player->play("Run");
	}
}

StringName PlayerGroundRunState::on_process(double delta) {
	// idle
	if (condition && condition->on_ground && (condition->ban_movement_input || condition->input_sign_x == 0) && condition->velocity.x == 0.0) {
		return PlayerGroundIdleState::get_class_static();
	}

	return parent_type::on_process(delta);
}

void PlayerGroundRunState::on_physics_process(double delta) {
	if (player && condition) {
		if (CharacterMovementComponent* character_movement_component = player->get_component<CharacterMovementComponent>()) {
			character_movement_component->input_move(delta,
					condition->velocity,
					condition->ban_movement_input ? 0 : condition->input_sign_x,
					character_movement_component->get_walk_acceleration(),
					character_movement_component->get_walk_deceleration(),
					character_movement_component->get_walk_turn_speed(),
					character_movement_component->get_walk_max_speed(),
					0.0);
		}
	}
}

void PlayerGroundRunState::exit() {
}
