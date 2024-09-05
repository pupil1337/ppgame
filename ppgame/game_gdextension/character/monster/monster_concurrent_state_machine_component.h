#ifndef MONSTER_CONCURRENT_STATE_MACHINE_COMPONENT_H
#define MONSTER_CONCURRENT_STATE_MACHINE_COMPONENT_H

#include <godot_cpp/classes/wrapped.hpp>
#include <godot_cpp/templates/vector.hpp>
using namespace godot;

#include "fsm/concurrent_state_machine_component.h"

class State;

//! 怪物并发状态机组件
class MonsterConcurrentStateMachineComponent : public ConcurrentStateMachineComponent {
	GDCLASS(MonsterConcurrentStateMachineComponent, ConcurrentStateMachineComponent)

protected:
	virtual StateCondition* _new_condition() override;
	virtual void _init_those_state_mem(const Vector<State*> p_states) override;
	virtual void _update_logic_condition() override;
	virtual void _update_physics_condition() override;

public:
	MonsterConcurrentStateMachineComponent() {}

	// ------------------------------------------

protected:
	static void _bind_methods() {}
};

#endif // MONSTER_CONCURRENT_STATE_MACHINE_COMPONENT_H
