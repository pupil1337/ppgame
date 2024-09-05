#ifndef MONSTER_BEHAVIOR_FINITE_STATE_MACHINE_COMPONENT_H
#define MONSTER_BEHAVIOR_FINITE_STATE_MACHINE_COMPONENT_H

#include <godot_cpp/classes/wrapped.hpp>
using namespace godot;

#include "fsm/finite_state_machine_component.h"

//! 怪物行为状态机
class MonsterBehaviorFiniteStateMachineComponent : public FiniteStateMachineComponent {
	GDCLASS(MonsterBehaviorFiniteStateMachineComponent, FiniteStateMachineComponent)

public:
	MonsterBehaviorFiniteStateMachineComponent() {}

	// ------------------------------------------

protected:
	static void _bind_methods() {}
};

#endif // MONSTER_BEHAVIOR_FINITE_STATE_MACHINE_COMPONENT_H
