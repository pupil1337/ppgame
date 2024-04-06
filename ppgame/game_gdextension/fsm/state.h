#ifndef STATE_H
#define STATE_H

#include <godot_cpp/classes/input_event.hpp>
#include <godot_cpp/classes/node.hpp>
#include <godot_cpp/classes/ref.hpp>
#include <godot_cpp/classes/wrapped.hpp>
#include <godot_cpp/variant/string_name.hpp>
using namespace godot;

class FiniteStateMachineComponent;

class State : public Node {
	GDCLASS(State, Node)

public:
	virtual void enter() = 0;
	virtual StringName on_input(const Ref<InputEvent>& p_event) = 0;
	virtual StringName on_process(double delta) = 0;
	virtual StringName on_physics_process(double delta) = 0;
	virtual void exit() = 0;

	// ------------------------------------------

public:
	virtual void _enter_tree() override;

protected:
	static void _bind_methods() {}
};

#endif // STATE_H
