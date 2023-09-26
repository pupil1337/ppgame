#ifndef FINITESTATEMACHINE
#define FINITESTATEMACHINE

#include "godot_cpp/classes/node.hpp"
#include "godot_cpp/templates/hash_map.hpp"

namespace godot {

class State;

class FiniteStateMachine : public Node {
	GDCLASS(FiniteStateMachine, Node)

protected:
	static void _bind_methods();

public:
	virtual void _ready() override;

//~Begin This Class

	void initialize_state_nodes(Node* node);

	void add_state(State* state);


	HashMap<StringName, State*> states;
};

}

#endif // FINITESTATEMACHINE