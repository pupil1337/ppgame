#ifndef PLAYER_WEAPON_FINITE_STATE_MACHINE_COMPONENT_H
#define PLAYER_WEAPON_FINITE_STATE_MACHINE_COMPONENT_H

#include <godot_cpp/classes/wrapped.hpp>
using namespace godot;

#include "fsm/finite_state_machine_component.h"

class PlayerFiniteStateMachineComponent;

//! 角色武器状态机
class PlayerWeaponFiniteStateMachineComponent : public FiniteStateMachineComponent {
	GDCLASS(PlayerWeaponFiniteStateMachineComponent, FiniteStateMachineComponent)

	friend PlayerFiniteStateMachineComponent;

	// ------------------------------------------

protected:
	static void _bind_methods() {}
};

#endif // PLAYER_WEAPON_FINITE_STATE_MACHINE_COMPONENT_H
