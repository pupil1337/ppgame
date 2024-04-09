#ifndef FINITE_STATE_MACHINE_COMPONENT_H
#define FINITE_STATE_MACHINE_COMPONENT_H

#include <godot_cpp/classes/input_event.hpp>
#include <godot_cpp/classes/ref.hpp>
#include <godot_cpp/classes/wrapped.hpp>
#include <godot_cpp/templates/hash_map.hpp>
#include <godot_cpp/variant/string_name.hpp>
using namespace godot;

#include "framework/component.h"

class State;

class FiniteStateMachineComponent : public Component {
	GDCLASS(FiniteStateMachineComponent, Component)

	friend State;

public:
	void on_start(const StringName& p_start_state);
	virtual void on_process(double p_delta);
	void on_physics_process(double p_delta);

private:
	void add_state(State* p_state);
	void _change_state(const StringName& p_new_state_name);

protected:
	State* curr_state = nullptr;
	HashMap<StringName, State*> states;

	// ------------------------------------------

protected:
	static void _bind_methods() {}
};

#endif // FINITE_STATE_MACHINE_COMPONENT_H
