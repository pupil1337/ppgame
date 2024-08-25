#ifndef FINITE_STATE_MACHINE_COMPONENT_H
#define FINITE_STATE_MACHINE_COMPONENT_H

#include <godot_cpp/classes/input_event.hpp>
#include <godot_cpp/classes/ref.hpp>
#include <godot_cpp/classes/wrapped.hpp>
#include <godot_cpp/templates/hash_map.hpp>
#include <godot_cpp/variant/packed_string_array.hpp>
#include <godot_cpp/variant/string_name.hpp>
#include <godot_cpp/variant/variant.hpp>
using namespace godot;

#include "framework/component.h"

class State;

//! 状态机
class FiniteStateMachineComponent : public Component {
	GDCLASS(FiniteStateMachineComponent, Component)

	friend State;

public:
	//! 逻辑帧
	virtual void on_process(double p_delta);
	//! 物理帧
	virtual void on_physics_process(double p_delta);
	//! 输入
	virtual void on_input(int p_fsm_input, const Variant& p_variant);

protected:
	//! 切换状态
	void _change_state(const StringName& p_new_state_name);

private:
	//! 增加状态
	bool add_state(State* p_state);

public:
	FiniteStateMachineComponent() {}

protected:
	State* curr_state = nullptr; //!< 当前状态
	HashMap<StringName, State*> states; //!< 状态名->状态节点

	// ------------------------------------------

public:
	virtual PackedStringArray _get_configuration_warnings() const override;

private:
	void set_init_state(State* p_init_state);
	State* get_init_state();

protected:
	static void _bind_methods();
};

#endif // FINITE_STATE_MACHINE_COMPONENT_H
