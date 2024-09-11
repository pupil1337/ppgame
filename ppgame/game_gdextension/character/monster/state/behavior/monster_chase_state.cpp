#include "monster_chase_state.h"

#include <godot_cpp/variant/string_name.hpp>

void MonsterChaseState::enter() {
}

StringName MonsterChaseState::on_process(double delta) {
	(void)delta;

	return StringName();
}

void MonsterChaseState::on_physics_process(double delta) {
	(void)delta;
}

void MonsterChaseState::exit() {
}
