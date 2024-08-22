#include "player_sword_attack.h"

#include <godot_cpp/variant/string_name.hpp>

void PlayerSwordAttack::enter() {
	play_animation("Weapon_Attack0");
}

StringName PlayerSwordAttack::on_process(double delta) {
	(void)delta;

	return StringName();
}

void PlayerSwordAttack::on_physics_process(double delta) {
	(void)delta;
}

void PlayerSwordAttack::exit() {
}
