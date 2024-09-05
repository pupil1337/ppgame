#include "monster_behavior_none_state.h"

#include <godot_cpp/variant/string_name.hpp>

void MonsterBehaviorNoneState::enter() {
}

StringName MonsterBehaviorNoneState::on_process(double delta) {
	(void)delta;
	return StringName();
}

void MonsterBehaviorNoneState::on_physics_process(double delta) {
	(void)delta;
}

void MonsterBehaviorNoneState::exit() {
}
