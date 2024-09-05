#ifndef PLAYER_CONCURRENT_STATE_MACHINE_COMPONENT_H
#define PLAYER_CONCURRENT_STATE_MACHINE_COMPONENT_H

#include <godot_cpp/classes/node2d.hpp>
#include <godot_cpp/classes/wrapped.hpp>
#include <godot_cpp/templates/vector.hpp>
#include <godot_cpp/variant/string_name.hpp>
using namespace godot;

#include "fsm/concurrent_state_machine_component.h"

class PlayerWeaponFiniteStateMachineComponent;
class PlayerMovementFiniteStateMachineComponent;

//! 角色并发状态机组件
class PlayerConcurrentStateMachineComponent : public ConcurrentStateMachineComponent {
	GDCLASS(PlayerConcurrentStateMachineComponent, ConcurrentStateMachineComponent)

	friend PlayerWeaponFiniteStateMachineComponent;
	friend PlayerMovementFiniteStateMachineComponent;

private:
	//! 动画结束信号
	void _animation_finished(const StringName& p_anim_name);
	//! 实体进入近战攻击区域
	void _body_enter_melee_attack(Node2D* p_body);
	//! 实体退出近战攻击区域
	void _body_exit_melee_attack(Node2D* p_body);

private:
	//! 更新进入MovementNoneState
	void condition_add_movement_none_state(int p_count);
	//! 更新进入WeaponNoneState
	void condition_add_weapon_none_state(int p_count);
	//! 更新禁用进入移动时播放动画
	void condition_add_ban_movement_enter_anim(int p_count);
	//! 更新禁用移动输入
	void condition_add_ban_movement_input(int p_count);

protected:
	virtual StateCondition* _new_condition() override;
	virtual void _init_those_state_mem(const Vector<State*> p_states) override;
	virtual void _update_logic_condition() override;
	virtual void _update_physics_condition() override;

public:
	PlayerConcurrentStateMachineComponent() {}

	// ------------------------------------------

public:
	virtual void _ready() override;

protected:
	static void _bind_methods() {}
};

#endif // PLAYER_CONCURRENT_STATE_MACHINE_COMPONENT_H
