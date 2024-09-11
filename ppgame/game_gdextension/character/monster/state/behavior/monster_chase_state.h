#ifndef MONSTER_CHASE_STATE_H
#define MONSTER_CHASE_STATE_H

#include <godot_cpp/classes/wrapped.hpp>
#include <godot_cpp/variant/string_name.hpp>
using namespace godot;

#include "character/monster/state/monster_state.h"

//! 怪物追逐状态
class MonsterChaseState : public MonsterState {
	GDCLASS(MonsterChaseState, MonsterState)

public:
	virtual void enter() override;
	virtual StringName on_process(double delta) override;
	virtual void on_physics_process(double delta) override;
	virtual void exit() override;

public:
	MonsterChaseState() {}

	// ------------------------------------------

protected:
	static void _bind_methods() {}
};

#endif // MONSTER_CHASE_STATE_H
