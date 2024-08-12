#ifndef PLAYER_FINITE_STATE_MACHINE_COMPONENT_H
#define PLAYER_FINITE_STATE_MACHINE_COMPONENT_H

#include <godot_cpp/classes/wrapped.hpp>
using namespace godot;

#include "character/player/state/player_state_condition.h"
#include "framework/component.h"

class Player;
class PlayerInputComponent;
class PlayerMovementFiniteStateMachineComponent;
class PlayerWeaponFiniteStateMachineComponent;

//! 角色状态机组件
/*!
 * 这不是一个状态机, 而是包含多个状态机的组件\n
 * 角色状态机为"并发状态机", 其中每个状态机为"层次状态机"
 *
 * 层次状态机中状态继承关系例如:
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
class PlayerFiniteStateMachineComponent : public Component {
	GDCLASS(PlayerFiniteStateMachineComponent, Component)

private:
	//! 更新逻辑条件
	void _update_logic_condition();
	//! 更新物理条件
	void _update_physics_condition();

private:
	Player* player = nullptr; //!< 角色
	PlayerInputComponent* player_input_component = nullptr; //!< 角色-输入组件

	PlayerStateCondition condition; //!< 状态条件
	PlayerMovementFiniteStateMachineComponent* player_movement_fsm; //!< 角色-移动状态机
	PlayerWeaponFiniteStateMachineComponent* player_weapon_fsm; //!< 角色-武器状态机

	// ------------------------------------------

public:
	virtual void _ready() override;
	virtual void _process(double p_delta) override;
	virtual void _physics_process(double p_delta) override;

protected:
	static void _bind_methods() {}
};

#endif // PLAYER_FINITE_STATE_MACHINE_COMPONENT_H
