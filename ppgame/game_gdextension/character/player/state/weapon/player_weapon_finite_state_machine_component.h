#ifndef PLAYER_WEAPON_FINITE_STATE_MACHINE_COMPONENT_H
#define PLAYER_WEAPON_FINITE_STATE_MACHINE_COMPONENT_H

#include <godot_cpp/classes/wrapped.hpp>
#include <godot_cpp/variant/variant.hpp>
using namespace godot;

#include "character/player/state/player_finite_state_machine_base_component.h"

//! 角色武器状态机
class PlayerWeaponFiniteStateMachineComponent : public PlayerFiniteStateMachineBaseComponent {
	GDCLASS(PlayerWeaponFiniteStateMachineComponent, PlayerFiniteStateMachineBaseComponent)

public:
	virtual void on_input(int p_fsm_input, const Variant& p_variant) override;

public:
	PlayerWeaponFiniteStateMachineComponent() {}

	// ------------------------------------------

protected:
	static void _bind_methods() {}
};

#endif // PLAYER_WEAPON_FINITE_STATE_MACHINE_COMPONENT_H
