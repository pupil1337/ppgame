#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <godot_cpp/classes/input_event.hpp>
#include <godot_cpp/classes/node.hpp>
#include <godot_cpp/classes/ref.hpp>
#include <godot_cpp/classes/wrapped.hpp>
using namespace godot;

class Controller : public Node {
	GDCLASS(Controller, Node)

public:
	virtual void _process(double delta) override;
	virtual void _unhandled_input(const Ref<InputEvent>& p_event) override;

	// ------------------------------------------

	int index = 0;

protected:
	static void _bind_methods() {}
};

#endif // CONTROLLER_H
