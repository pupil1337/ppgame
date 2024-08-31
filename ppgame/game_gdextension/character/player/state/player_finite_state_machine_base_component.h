#ifndef PLAYER_FINITE_STATE_MACHINE_BASE_COMPONENT_H
#define PLAYER_FINITE_STATE_MACHINE_BASE_COMPONENT_H

#include <godot_cpp/classes/wrapped.hpp>
using namespace godot;

#include "character/player/state/player_state_condition.h"
#include "fsm/finite_state_machine_component.h"

class PlayerFiniteStateMachineComponent;

//! 角色状态机基类
class PlayerFiniteStateMachineBaseComponent : public FiniteStateMachineComponent {
	GDCLASS(PlayerFiniteStateMachineBaseComponent, FiniteStateMachineComponent)

	friend PlayerFiniteStateMachineComponent;

public:
	PlayerFiniteStateMachineBaseComponent() {}

protected:
	const PlayerStateCondition* condition = nullptr; //!< 状态条件
	PlayerFiniteStateMachineComponent* player_fsm_component = nullptr; //!< 状态机组件

	// ------------------------------------------

protected:
	static void _bind_methods() {}
	void _notification(int p_what);
};

#endif // PLAYER_FINITE_STATE_MACHINE_BASE_COMPONENT_H
