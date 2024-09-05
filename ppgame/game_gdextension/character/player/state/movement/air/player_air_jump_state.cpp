#include "player_air_jump_state.h"

#include <godot_cpp/core/defs.hpp>
#include <godot_cpp/variant/string_name.hpp>
#include <godot_cpp/variant/vector2.hpp>

#include "character/character_movement_component.h"
#include "character/player/player.h"
#include "character/player/state/movement/air/player_air_fall_state.h"
#include "character/player/state/player_state_condition.h"
#include "utils/math_utils.h"

void PlayerAirJumpState::enter() {
	desire_jump = true;
	if (animation_player && condition && !condition->ban_movement_enter_anim) {
		animation_player->play("Jump");
	}
}

StringName PlayerAirJumpState::on_process(double delta) {
	if (desire_jump) {
		return StringName();
	}

	// fall
	if (condition && !condition->on_ground && condition->velocity.y > 0.0) {
		return PlayerAirFallState::get_class_static();
	}

	return parent_type::on_process(delta);
}

void PlayerAirJumpState::on_physics_process(double delta) {
	if (player && condition) {
		if (CharacterMovementComponent* character_movement_component = player->get_component<CharacterMovementComponent>()) {
			if (desire_jump) {
				character_movement_component->jump(condition->velocity, character_movement_component->get_jump_height(), character_movement_component->get_jump_duration());

				desire_jump = false;
				return;
			}

			real_t gravity = MathUtils::calculate_jump_gravity(character_movement_component->get_jump_height(), character_movement_component->get_jump_duration());
			character_movement_component->input_move(
					delta,
					condition->velocity,
					condition->ban_movement_input ? 0 : condition->input_sign_x,
					character_movement_component->get_walk_acceleration(),
					character_movement_component->get_walk_acceleration(),
					character_movement_component->get_walk_turn_speed(),
					character_movement_component->get_walk_max_speed(),
					gravity);
		}
	}
}

void PlayerAirJumpState::exit() {
}
