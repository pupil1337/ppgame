#include "player_weapon_none_state.h"

#include <godot_cpp/variant/string_name.hpp>

#include "character/player/state/player_state_condition.h"
#include "sword/player_sword_attack.h"

PlayerWeaponNoneState::PlayerWeaponNoneState() {
	is_default_state = true;
}

StringName PlayerWeaponNoneState::on_process(double delta) {
	(void)delta;

	if (condition && condition->just_pressed_attack) {
		// TODO
		return PlayerSwordAttack::get_class_static();
	}

	return StringName();
}
