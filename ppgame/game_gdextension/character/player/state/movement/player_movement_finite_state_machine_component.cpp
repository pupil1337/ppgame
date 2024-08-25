#include "player_movement_finite_state_machine_component.h"

#include <godot_cpp/variant/variant.hpp>

#include "character/player/player_finite_state_machine_component.h"
#include "character/player/state/movement/ground/player_ground_idle_state.h"
#include "character/player/state/movement/player_movement_none_state.h"
#include "character/player/state/player_fsm_input_types.h"
#include "fsm/state.h"

void PlayerMovementFiniteStateMachineComponent::on_input(int p_fsm_input, const Variant& p_variant) {
	switch ((PlayerFSMInput)p_fsm_input) {
		case PlayerFSMInput::To_Movement_None_State: {
			if (player_fsm_component) {
				player_fsm_component->condition_add_movement_none_state(p_variant);
			}

			if (condition->movement_none_state > 0) {
				if (curr_state->get_class() != PlayerMovementNoneState::get_class_static()) {
					_change_state(PlayerMovementNoneState::get_class_static());
					return;
				}
			} else {
				if (curr_state->get_class() == PlayerMovementNoneState::get_class_static()) {
					_change_state(PlayerGroundIdleState::get_class_static());
					return;
				}
			}
		} break;

		case PlayerFSMInput::Ban_Movement_Enter_Anim: {
			if (player_fsm_component) {
				player_fsm_component->condition_add_ban_movement_enter_anim(p_variant);
			}
		} break;

		case PlayerFSMInput::Reset_Movement_To_Idle: {
			_change_state(PlayerGroundIdleState::get_class_static());
		} break;

		default:
			break;
	}

	parent_type::on_input(p_fsm_input, p_variant);
}
