#include "player_air_fall_state.h"

#include <godot_cpp/core/defs.hpp>
#include <godot_cpp/variant/string_name.hpp>

#include "character/character_movement_component.h"
#include "character/player/player.h"
#include "character/player/state/movement/air/player_air_jump_state.h"
#include "character/player/state/player_state_condition.h"
#include "utils/math_utils.h"

void PlayerAirFallState::enter() {
	if (animation_player && condition && !condition->ban_movement_enter_anim) {
		animation_player->play("Fall");
	}
}

StringName PlayerAirFallState::on_process(double delta) {
	// jump
	if (condition && !condition->ban_movement_input && condition->just_pressed_jump && condition->can_jump) {
		return PlayerAirJumpState::get_class_static();
	}

	return parent_type::on_process(delta);
}

void PlayerAirFallState::on_physics_process(double delta) {
	if (player && condition) {
		if (CharacterMovementComponent* character_movement_component = player->get_component<CharacterMovementComponent>()) {
			real_t gravity = MathUtils::calculate_fall_gravity(character_movement_component->get_jump_height(), character_movement_component->get_jump_duration(), character_movement_component->get_fall_gravity_multiplayer());
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

void PlayerAirFallState::exit() {
}
