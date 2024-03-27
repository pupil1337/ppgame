#ifndef PLAYER_FINITE_STATE_MACHINE_COMPONENT_H
#define PLAYER_FINITE_STATE_MACHINE_COMPONENT_H

#include "fsm/finite_state_machine_component.h"

class PlayerFiniteStateMachineComponent : public FiniteStateMachineComponent {
	GDCLASS(PlayerFiniteStateMachineComponent, FiniteStateMachineComponent)

protected:
	static void _bind_methods();
};

#endif // PLAYER_FINITE_STATE_MACHINE_COMPONENT_H
