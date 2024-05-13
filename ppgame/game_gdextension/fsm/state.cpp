#include "state.h"

#include <godot_cpp/classes/engine.hpp>
#include <godot_cpp/classes/node.hpp>
#include <godot_cpp/classes/object.hpp>

#include "fsm/finite_state_machine_component.h"

void State::_notification(int p_what) {
	if (!Engine::get_singleton()->is_editor_hint()) {
		if (p_what == NOTIFICATION_PARENTED) {
			_register_state(this);
		}
	}
}

void State::_register_state(Node* p_node) {
	if (p_node) {
		if (Node* parent = p_node->get_parent()) {
			if (parent != p_node) {
				FiniteStateMachineComponent* fsm = dynamic_cast<FiniteStateMachineComponent*>(parent);
				if (fsm) {
					fsm->add_state(this);
				} else {
					_register_state(parent);
				}
			}
		}
	}
}
