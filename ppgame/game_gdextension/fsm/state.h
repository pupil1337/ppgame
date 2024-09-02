#ifndef STATE_H
#define STATE_H

#include <godot_cpp/classes/node.hpp>
#include <godot_cpp/classes/wrapped.hpp>
#include <godot_cpp/variant/string_name.hpp>
using namespace godot;

class FiniteStateMachineComponent;

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

private:
	//! 注册状态
	/*!
	 * 将此状态注册到FiniteStateMachineComponent上
	 * _notification->NOTIFICATION_PARENTED时自动调用
	 * \param p_node 需要找到父节点为FiniteStateMachineComponent的节点. 初始值为this, 如果父节点不是FiniteStateMachineComponent则递归父节点查找
	 * \return 是否注册成功
	 */
	bool _register_state(Node* p_node);

public:
	State() {}

protected:
	bool is_default_state = false; // !< 是否是默认状态

	// ------------------------------------------

protected:
	static void _bind_methods() {}
	void _notification(int p_what);
};

#endif // STATE_H
