#ifndef PLAYER_FINITE_STATE_MACHINE_COMPONENT_H
#define PLAYER_FINITE_STATE_MACHINE_COMPONENT_H

#include <godot_cpp/classes/wrapped.hpp>
#include <godot_cpp/core/defs.hpp>
using namespace godot;

#include "character/player/state/player_state_condition.h"
#include "fsm/finite_state_machine_component.h"

class Player;
class PlayerInputComponent;

//! 角色状态机
/*!
 * 这是一个分层状态机
 *
 * 状态继承关系例如:
 *
 \verbatim
								 PlayerGroundIdleState
								/
			   PlayerGroundState
			  /                 \
			 /                   PlayerGroundRunState
  PlayerState
			 \                PlayerAirJumpState
			  \              /
			   PlayerAirState
							 \
							  PlayerAirFallState

  PlayerGroundState(状态基类)实现从Ground到PlayerAirJumpState(其他状态层类型)的转换判断
  PlayerAirJumpState(状态子类)实现从AirJump到PlayerAirFallState(同层状态类型)的转换判断
 \endverbatim
 */
class PlayerFiniteStateMachineComponent : public FiniteStateMachineComponent {
	GDCLASS(PlayerFiniteStateMachineComponent, FiniteStateMachineComponent)

public:
	virtual void on_process(double p_delta) override;
	virtual void on_physics_process(double p_delta) override;

private:
	//! 更新逻辑条件
	void _update_logic_condition();
	//! 更新物理条件
	void _update_physics_condition();

private:
	Player* player = nullptr; //!< 角色
	PlayerInputComponent* player_input_component = nullptr; //!< 角色-输入组件

	PlayerStateCondition condition; //!< 状态条件

	// ------------------------------------------

public:
	virtual void _ready() override;

protected:
	static void _bind_methods() {}
};

#endif // PLAYER_FINITE_STATE_MACHINE_COMPONENT_H
