#include "finiteStateMachine.h"

#include <godot_cpp/variant/utility_functions.hpp>
#include "state.h"

using namespace godot;

void FiniteStateMachine::_bind_methods() {

}

void FiniteStateMachine::_ready() {
	initialize_state_nodes(this);
}

void FiniteStateMachine::initialize_state_nodes(Node* node) {
	for (int i = 0; i < node->get_child_count(true); ++i) {
		Node* child = node->get_child(i, true);
		if (State* state = cast_to<State>(child)) {
			add_state(state);
		}
		else {
			initialize_state_nodes(child);
		}
	}
}

void FiniteStateMachine::add_state(State* state) {
	if (state->is_inside_tree())
	{
		UtilityFunctions::print(state->get_name());
		states[state->get_name()] = get_node<State>(state->get_path());
	}
}
