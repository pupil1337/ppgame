#include "state.h"

#include <godot_cpp/classes/engine.hpp>
#include <godot_cpp/classes/node.hpp>
#include <godot_cpp/classes/object.hpp>
#include <godot_cpp/core/error_macros.hpp>

#include "fsm/finite_state_machine_component.h"

void State::_notification(int p_what) {
	if (!Engine::get_singleton()->is_editor_hint()) {
		if (p_what == NOTIFICATION_PARENTED) {
			if (!_register_state(this)) {
				ERR_PRINT_ED("_register_state->" + get_class());
			}
		}
	}
}

bool State::_register_state(Node* p_node) {
	if (p_node) {
		if (Node* parent = p_node->get_parent()) {
			if (parent != p_node) {
				FiniteStateMachineComponent* fsm = Object::cast_to<FiniteStateMachineComponent>(parent);
				if (fsm != nullptr) {
					return fsm->add_state(this);
				} else {
					return _register_state(parent);
				}
			}
		}
	}

	return false;
}
