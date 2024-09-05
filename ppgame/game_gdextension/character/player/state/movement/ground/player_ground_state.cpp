#include "player_ground_state.h"

#include <godot_cpp/variant/string_name.hpp>
#include <godot_cpp/variant/utility_functions.hpp>
#include <godot_cpp/variant/vector2.hpp>

#include "character/character_movement_component.h"
#include "character/player/player.h"
#include "character/player/state/movement/air/player_air_fall_state.h"
#include "character/player/state/movement/air/player_air_jump_state.h"
#include "character/player/state/player_state_condition.h"

StringName PlayerGroundState::on_process(double delta) {
	(void)delta;

	if (condition) {
		// air state
		// down jump
		if (condition && !condition->ban_movement_input && condition->input_sign_y > 0 && condition->just_pressed_jump) {
			if (CharacterMovementComponent* character_movement_component = player->get_component<CharacterMovementComponent>()) {
				if (character_movement_component->down_jump()) {
					return PlayerAirFallState::get_class_static();
				}
			}
		}
		// jump
		if (condition && !condition->ban_movement_input && condition->just_pressed_jump && condition->can_jump) {
			return PlayerAirJumpState::get_class_static();
		}
		// fall
		if (condition && !condition->on_ground) {
			return PlayerAirFallState::get_class_static();
		}
	}

	return StringName();
}
