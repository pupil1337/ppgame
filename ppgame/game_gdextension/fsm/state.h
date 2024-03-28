#ifndef STATE_H
#define STATE_H

#include <godot_cpp/classes/input_event.hpp>
#include <godot_cpp/classes/node.hpp>
#include <godot_cpp/classes/ref.hpp>
#include <godot_cpp/variant/string_name.hpp>
using namespace godot;

class State : public Node {
	GDCLASS(State, Node)

public:
	virtual void enter() {};
	virtual StringName on_input(const Ref<InputEvent>& p_event) { return StringName(); }
	virtual StringName on_process(double delta) { return StringName(); };
	virtual StringName on_physics_process(double delta) { return StringName(); };
	virtual void exit() {};

	// ------------------------------------------

protected:
	static void _bind_methods() {}
};

#endif // STATE_H
