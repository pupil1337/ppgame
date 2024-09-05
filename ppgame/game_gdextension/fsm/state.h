#ifndef STATE_H
#define STATE_H

#include <godot_cpp/classes/node.hpp>
#include <godot_cpp/classes/wrapped.hpp>
#include <godot_cpp/variant/string_name.hpp>
using namespace godot;

#include "fsm/finite_state_machine_component.h"

//! State类
/*!
 * 状态机中的状态
 */
class State : public Node {
	GDCLASS(State, Node)

	friend FiniteStateMachineComponent;

public:
	//! 进入状态
	virtual void enter() = 0;
	//! 逻辑帧
	virtual StringName on_process(double delta) = 0;
	//! 物理帧
	virtual void on_physics_process(double delta) = 0;
	//! 退出状态
	virtual void exit() = 0;

	//! 输入
	virtual StringName on_input(int p_fsm_input, const Variant& p_variant) { return StringName(); }

public:
	//! 获取条件
	template <typename T>
	const T* get_condition() const {
		if (owner_fsm) {
			return static_cast<T*>(owner_fsm->get_condition<T>());
		}

		return nullptr;
	}

public:
	State() {}

protected:
	bool is_default_state = false; //!< 是否是默认状态
	FiniteStateMachineComponent* owner_fsm = nullptr; //!< 拥有此状态的状态机

	// ------------------------------------------

protected:
	static void _bind_methods() {}
	void _notification(int p_what);
};

#endif // STATE_H
