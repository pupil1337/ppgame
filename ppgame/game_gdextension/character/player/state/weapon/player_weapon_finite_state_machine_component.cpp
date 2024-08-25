#include "player_weapon_finite_state_machine_component.h"

#include <godot_cpp/variant/variant.hpp>

#include "character/player/player_finite_state_machine_component.h"
#include "character/player/state/player_fsm_input_types.h"
#include "character/player/state/weapon/player_weapon_none_state.h"
#include "fsm/state.h"

void PlayerWeaponFiniteStateMachineComponent::on_input(int p_fsm_input, const Variant& p_variant) {
	if ((PlayerFSMInput)p_fsm_input == PlayerFSMInput::To_Weapon_None_State) {
		if (player_fsm_component) {
			player_fsm_component->condition_add_weapon_none_state(p_variant);
		}

		if (condition->weapon_none_state > 0) {
			if (curr_state->get_class() != PlayerWeaponNoneState::get_class_static()) {
				_change_state(PlayerWeaponNoneState::get_class_static());
				return;
			}
		}
	}

	parent_type::on_input(p_fsm_input, p_variant);
}
