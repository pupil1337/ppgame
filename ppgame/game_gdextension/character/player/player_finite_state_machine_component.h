#ifndef PLAYER_FINITE_STATE_MACHINE_COMPONENT_H
#define PLAYER_FINITE_STATE_MACHINE_COMPONENT_H

#include <godot_cpp/classes/wrapped.hpp>
using namespace godot;

#include "fsm/finite_state_machine_component.h"

class PlayerFiniteStateMachineComponent : public FiniteStateMachineComponent {
	GDCLASS(PlayerFiniteStateMachineComponent, FiniteStateMachineComponent)

public:
	virtual void _ready() override;

	// ------------------------------------------

protected:
	static void _bind_methods() {}
};

#endif // PLAYER_FINITE_STATE_MACHINE_COMPONENT_H
