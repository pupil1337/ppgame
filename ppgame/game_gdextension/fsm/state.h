#ifndef STATE_H
#define STATE_H

#include <godot_cpp/classes/input_event.hpp>
#include <godot_cpp/classes/node.hpp>
#include <godot_cpp/classes/ref.hpp>
#include <godot_cpp/classes/wrapped.hpp>
using namespace godot;

namespace godot {
class StringName;
}

class State : public Node {
	GDCLASS(State, Node)

public:
	virtual void enter() = 0;
	virtual StringName on_input(const Ref<InputEvent>& p_event) = 0;
	virtual StringName on_process(double delta) = 0;
	virtual StringName on_physics_process(double delta) = 0;
	virtual void exit() = 0;

	// ------------------------------------------

protected:
	static void _bind_methods() {}
};

#endif // STATE_H
