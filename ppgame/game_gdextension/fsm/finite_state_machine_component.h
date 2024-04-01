#ifndef FINITE_STATE_MACHINE_COMPONENT_H
#define FINITE_STATE_MACHINE_COMPONENT_H

#include <godot_cpp/classes/input_event.hpp>
#include <godot_cpp/classes/ref.hpp>
#include <godot_cpp/classes/wrapped.hpp>
#include <godot_cpp/templates/hash_map.hpp>
using namespace godot;

#include "framework/component.h"

namespace godot {
class StringName;
}
class State;

class FiniteStateMachineComponent : public Component {
	GDCLASS(FiniteStateMachineComponent, Component)

public:
	void on_start(const StringName& p_start_state);
	void on_input(const Ref<InputEvent>& p_event);
	void on_process(double p_delta);
	void on_physics_process(double p_delta);

private:
	void _change_state(const StringName& p_new_state_name);

	State* curr_state = nullptr;
	HashMap<StringName, State*> states;

	// ------------------------------------------

public:
	virtual void _ready() override;

protected:
	static void _bind_methods() {}
};

#endif // FINITE_STATE_MACHINE_COMPONENT_H
