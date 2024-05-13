#ifndef STATE_H
#define STATE_H

#include <godot_cpp/classes/node.hpp>
#include <godot_cpp/classes/wrapped.hpp>
#include <godot_cpp/variant/string_name.hpp>
using namespace godot;

class State : public Node {
	GDCLASS(State, Node)

public:
	virtual void enter() = 0;
	virtual StringName on_process(double delta) = 0;
	virtual void on_physics_process(double delta) = 0;
	virtual void exit() = 0;

private:
	void _register_state(Node* p_node);

	// ------------------------------------------

protected:
	void _notification(int p_what);
	static void _bind_methods() {}
};

#endif // STATE_H
