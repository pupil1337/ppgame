#ifndef PLAYER_WEAPON_FINITE_STATE_MACHINE_COMPONENT_H
#define PLAYER_WEAPON_FINITE_STATE_MACHINE_COMPONENT_H

#include <godot_cpp/classes/wrapped.hpp>
#include <godot_cpp/variant/variant.hpp>
using namespace godot;

#include "fsm/finite_state_machine_component.h"

class PlayerFiniteStateMachineComponent;
struct PlayerStateCondition;

//! 角色武器状态机
class PlayerWeaponFiniteStateMachineComponent : public FiniteStateMachineComponent {
	GDCLASS(PlayerWeaponFiniteStateMachineComponent, FiniteStateMachineComponent)

	friend PlayerFiniteStateMachineComponent;

public:
	virtual void on_input(int p_fsm_input, const Variant& p_variant) override;

public:
	PlayerWeaponFiniteStateMachineComponent() {}

protected:
	const PlayerStateCondition* condition = nullptr; //!< 状态条件
	PlayerFiniteStateMachineComponent* player_fsm_component = nullptr; //!< 状态机组件

	// ------------------------------------------

protected:
	static void _bind_methods() {}
};

#endif // PLAYER_WEAPON_FINITE_STATE_MACHINE_COMPONENT_H
