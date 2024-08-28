#ifndef PLAYER_FINITE_STATE_MACHINE_COMPONENT_H
#define PLAYER_FINITE_STATE_MACHINE_COMPONENT_H

#include <godot_cpp/classes/animation_player.hpp>
#include <godot_cpp/classes/wrapped.hpp>
#include <godot_cpp/variant/packed_string_array.hpp>
#include <godot_cpp/variant/string_name.hpp>
using namespace godot;

#include "character/player/state/player_fsm_input_types.h"
#include "character/player/state/player_state_condition.h"
#include "framework/component.h"

class Player;
class PlayerInputComponent;
class PlayerMovementFiniteStateMachineComponent;
class PlayerWeaponFiniteStateMachineComponent;

//! 角色状态机组件
/*!
 * 这不是一个状态机, 而是包含多个状态机的组件\n
 * 此为"并发状态机", 其中每个状态机为"层次状态机"
 *
 * "并发状态机"即同时拥有多个状态机\n
 * 若角色有n种状态、武器有m种状态, 那么使用"并发状态机"只需要定义n+m种状态; 传统状态机需要nm种状态
 *
 * 注: "层次状态机"中状态继承关系例如:
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

	friend PlayerMovementFiniteStateMachineComponent;
	friend PlayerWeaponFiniteStateMachineComponent;

public:
	//! 状态机输入
	void on_input(PlayerFSMInput p_fsm_input, const Variant& p_variant);

private:
	//! 更新逻辑条件
	void _update_logic_condition();
	//! 更新物理条件
	void _update_physics_condition();

	//! 动画结束信号
	void _animation_finished(const StringName& p_anim_name);

private:
	//! 更新进入MovementNoneState
	void condition_add_movement_none_state(int p_count);
	//! 更新进入WeaponNoneState
	void condition_add_weapon_none_state(int p_count);
	//! 更新禁用进入移动时播放动画
	void condition_add_ban_movement_enter_anim(int p_count);
	//! 更新禁用移动输入
	void condition_add_ban_movement_input(int p_count);

public:
	PlayerFiniteStateMachineComponent() {}

private:
	Player* player = nullptr; //!< 角色
	PlayerInputComponent* player_input_component = nullptr; //!< 角色-输入组件
	AnimationPlayer* animation_player = nullptr; //!< 角色-动画播放器

	PlayerStateCondition condition; //!< 状态条件
	PlayerMovementFiniteStateMachineComponent* player_movement_fsm = nullptr; //!< 角色-移动状态机
	PlayerWeaponFiniteStateMachineComponent* player_weapon_fsm = nullptr; //!< 角色-武器状态机

	// ------------------------------------------

private:
	void set_player_movement_fsm(PlayerMovementFiniteStateMachineComponent* p_player_movement_fsm);
	void set_player_weapon_fsm(PlayerWeaponFiniteStateMachineComponent* p_player_weapon_fsm);
	PlayerMovementFiniteStateMachineComponent* get_player_movement_fsm();
	PlayerWeaponFiniteStateMachineComponent* get_player_weapon_fsm();

public:
	virtual PackedStringArray _get_configuration_warnings() const override;
	virtual void _ready() override;
	virtual void _process(double p_delta) override;
	virtual void _physics_process(double p_delta) override;

protected:
	static void _bind_methods();
	void _notification(int p_what);
};

#endif // PLAYER_FINITE_STATE_MACHINE_COMPONENT_H
