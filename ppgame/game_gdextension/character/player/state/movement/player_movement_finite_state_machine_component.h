#ifndef PLAYER_MOVEMENT_FINITE_STATE_MACHINE_COMPONENT_H
#define PLAYER_MOVEMENT_FINITE_STATE_MACHINE_COMPONENT_H

#include <godot_cpp/classes/wrapped.hpp>
using namespace godot;

#include "fsm/finite_state_machine_component.h"

class PlayerFiniteStateMachineComponent;

//! 角色移动状态机
class PlayerMovementFiniteStateMachineComponent : public FiniteStateMachineComponent {
	GDCLASS(PlayerMovementFiniteStateMachineComponent, FiniteStateMachineComponent)

	friend PlayerFiniteStateMachineComponent;

public:
	PlayerMovementFiniteStateMachineComponent() {}

	// ------------------------------------------

protected:
	static void _bind_methods() {}
};

#endif // PLAYER_MOVEMENT_FINITE_STATE_MACHINE_COMPONENT_H
