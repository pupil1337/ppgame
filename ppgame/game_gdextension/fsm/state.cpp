#include "state.h"

#include <functional>
#include <godot_cpp/classes/node.hpp>
#include <godot_cpp/classes/object.hpp>

#include "fsm/finite_state_machine_component.h"

void State::_enter_tree() {
	super::_enter_tree();

	std::function<void(Node * p_node)> _register_state;
	_register_state = [&_register_state, this](Node* p_node) -> void {
		if (p_node) {
			if (Node* parent = p_node->get_parent()) {
				if (parent != p_node) {
					FiniteStateMachineComponent* fsm = Object::cast_to<FiniteStateMachineComponent>(parent);
					if (fsm) {
						fsm->add_state(this);
					} else {
						_register_state(parent);
					}
				}
			}
		}
	};

	_register_state(this);
}
