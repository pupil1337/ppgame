#ifndef CONCURRENT_STATE_MACHINE_COMPONENT_H
#define CONCURRENT_STATE_MACHINE_COMPONENT_H

#include <godot_cpp/classes/wrapped.hpp>
#include <godot_cpp/core/defs.hpp>
#include <godot_cpp/templates/vector.hpp>
#include <godot_cpp/variant/variant.hpp>
using namespace godot;

#include "framework/component.h"

class State;
class FiniteStateMachineComponent;
struct StateCondition;

//! 并发状态机组件
/*!
 * 这不是一个状态机, 而是包含多个状态机的组件\n
 * 其中每个状态机为"层次状态机"
 *
 * "并发状态机"即同时拥有多个状态机\n
 * 若玩家有n种状态、武器有m种状态, 那么使用"并发状态机"只需要定义n+m种状态; 传统状态机需要nm种状态
 */
class ConcurrentStateMachineComponent : public Component {
	GDCLASS(ConcurrentStateMachineComponent, Component)

	friend FiniteStateMachineComponent;

public:
	//! 状态机输入
	void on_input(int p_fsm_input, const Variant& p_variant);

public:
	//! 获取条件
	_FORCE_INLINE_ const StateCondition* get_condition() { return condition; }

protected:
	//! new此状态机Condition
	virtual StateCondition* _new_condition() = 0;
	//! 初始化这些状态成员变量缓存
	virtual void _init_those_state_mem(const Vector<State*> p_states) = 0;
	//! 更新逻辑条件
	virtual void _update_logic_condition() = 0;
	//! 更新物理条件
	virtual void _update_physics_condition() = 0;

public:
	ConcurrentStateMachineComponent() {}

protected:
	Vector<FiniteStateMachineComponent*> fsms; //!< 状态机
	StateCondition* condition = nullptr; //!< 条件

	// ------------------------------------------

public:
	virtual void _ready() override;
	virtual void _process(double p_delta) override;
	virtual void _physics_process(double p_delta) override;

protected:
	static void _bind_methods() {}
	void _notification(int p_what);
};

#endif // CONCURRENT_STATE_MACHINE_COMPONENT_H
