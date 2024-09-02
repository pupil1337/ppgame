#include "player_sword_attack.h"

#include <godot_cpp/variant/string_name.hpp>
#include <godot_cpp/variant/utility_functions.hpp>

#include "character/player/player_finite_state_machine_component.h"
#include "character/player/state/player_fsm_input_types.h"
#include "character/player/state/weapon/player_weapon_none_state.h"

void PlayerSwordAttack::enter() {
	if (animation_player) {
		animation_player->play("Weapon_Attack0");
	}

	if (player_fsm_component) {
		player_fsm_component->on_input(PlayerFSMInput::Ban_Movement_Enter_Anim, 1);
		player_fsm_component->on_input(PlayerFSMInput::Ban_Movement_Input, 1);
	}
}

StringName PlayerSwordAttack::on_process(double delta) {
	(void)delta;

	return StringName();
}

void PlayerSwordAttack::on_physics_process(double delta) {
	(void)delta;
}

StringName PlayerSwordAttack::on_input(int p_fsm_input, const Variant& p_variant) {
	if (p_fsm_input == (int)PlayerFSMInput::Animation_Finished) {
		return PlayerWeaponNoneState::get_class_static();
	} else if (p_fsm_input == (int)PlayerFSMInput::Body_Enter_Melee_Attack) {
		UtilityFunctions::print("PlayerSwordAttack- Body_Enter_Melee_Attack: ", p_variant.operator Object*()->get_class());
	}

	return parent_type::on_input(p_fsm_input, p_variant);
}

void PlayerSwordAttack::exit() {
	if (player_fsm_component) {
		player_fsm_component->on_input(PlayerFSMInput::Ban_Movement_Enter_Anim, -1);
		player_fsm_component->on_input(PlayerFSMInput::Ban_Movement_Input, -1);
		player_fsm_component->on_input(PlayerFSMInput::Reset_Movement_To_Idle, nullptr);
	}

	if (player_melee_attack_shape) {
		player_melee_attack_shape->set_disabled(true);
	}
}
