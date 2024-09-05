#ifndef MONSTER_BEHAVIOR_NONE_STATE
#define MONSTER_BEHAVIOR_NONE_STATE

#include <godot_cpp/classes/wrapped.hpp>
#include <godot_cpp/variant/string_name.hpp>
using namespace godot;

#include "character/monster/state/monster_state.h"

//! 怪物行为None
class MonsterBehaviorNoneState : public MonsterState {
	GDCLASS(MonsterBehaviorNoneState, MonsterState)

public:
	virtual void enter() override;
	virtual StringName on_process(double delta) override;
	virtual void on_physics_process(double delta) override;
	virtual void exit() override;

public:
	MonsterBehaviorNoneState() {}

	// ------------------------------------------

protected:
	static void _bind_methods() {}
};

#endif // MONSTER_BEHAVIOR_NONE_STATE
