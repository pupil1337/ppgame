#ifndef STATE_H
#define STATE_H

#include <godot_cpp/classes/node.hpp>

namespace godot {

class State : public Node {
	GDCLASS(State, Node)

protected:
	static void _bind_methods();
};

}

#endif // STATE_H