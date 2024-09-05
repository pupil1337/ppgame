#ifndef FINITE_STATE_MACHINE_COMPONENT_H
#define FINITE_STATE_MACHINE_COMPONENT_H

#include <godot_cpp/classes/wrapped.hpp>
#include <godot_cpp/templates/hash_map.hpp>
#include <godot_cpp/variant/string_name.hpp>
#include <godot_cpp/variant/variant.hpp>
using namespace godot;

#include "framework/component.h"
#include "fsm/concurrent_state_machine_component.h"

class State;
class ConcurrentStateMachineComponent;

//! 状态机
/*!
 * 此状态机实现是"层次状态机"\n
 * "层次状态机"中状态继承关系例如:
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
class FiniteStateMachineComponent : public Component {
	GDCLASS(FiniteStateMachineComponent, Component)

	friend State;
	friend ConcurrentStateMachineComponent;

public:
	//! 开始状态机
	void on_start();
	//! 逻辑帧
	virtual void on_process(double p_delta);
	//! 物理帧
	virtual void on_physics_process(double p_delta);
	//! 输入
	virtual void on_input(int p_fsm_input, const Variant& p_variant);

protected:
	//! 切换状态
	void _change_state(const StringName& p_new_state_name);

	//! 获取条件
	template <typename T>
	const T* get_condition() const {
		if (owner_csm_component) {
			return static_cast<const T*>(owner_csm_component->get_condition());
		}

		return nullptr;
	}

private:
	//! 增加状态
	bool add_state(State* p_state);

public:
	FiniteStateMachineComponent() {}

protected:
	State* curr_state = nullptr; //!< 当前状态
	HashMap<StringName, State*> states; //!< 状态名->状态节点
	ConcurrentStateMachineComponent* owner_csm_component = nullptr; //!< 拥有此状态机的并发状态机组件

	// ------------------------------------------

protected:
	static void _bind_methods() {}
	void _notification(int p_what);
};

#endif // FINITE_STATE_MACHINE_COMPONENT_H
