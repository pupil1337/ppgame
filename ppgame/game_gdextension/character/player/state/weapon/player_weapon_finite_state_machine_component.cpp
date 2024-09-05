#include "player_weapon_finite_state_machine_component.h"

#include <godot_cpp/variant/variant.hpp>

#include "character/player/player_concurrent_state_machine_component.h"
#include "character/player/state/player_fsm_input_types.h"
#include "character/player/state/player_state_condition.h"
#include "character/player/state/weapon/player_weapon_none_state.h"
#include "framework/actor.h"

void PlayerWeaponFiniteStateMachineComponent::on_input(int p_fsm_input, const Variant& p_variant) {
	if ((PlayerFSMInput)p_fsm_input == PlayerFSMInput::To_Weapon_None_State) {
		if (actor) {
			if (PlayerConcurrentStateMachineComponent* player_csm_component = actor->get_component<PlayerConcurrentStateMachineComponent>()) {
				player_csm_component->condition_add_weapon_none_state(p_variant);
			}
		}

		if (const PlayerStateCondition* condition = get_condition<PlayerStateCondition>()) {
			if (condition && condition->weapon_none_state > 0) {
				if (curr_state->get_class() != PlayerWeaponNoneState::get_class_static()) {
					_change_state(PlayerWeaponNoneState::get_class_static());
					return;
				}
			}
		}
	}

	parent_type::on_input(p_fsm_input, p_variant);
}
