#include "finite_state_machine_component.h"

#include "fsm/state.h"
#include <functional>

void FiniteStateMachineComponent::_ready() {
	std::function<void(Node*)> _add_state_nodes;
	_add_state_nodes = [this, &_add_state_nodes](Node* p_node) -> void {
		for (int i = 0; i < p_node->get_child_count(true); ++i) {
			Node* child = p_node->get_child(i, true);
			if (State* state = Object::cast_to<State>(child)) {
				states[child->get_class_static()] = state;
			} else {
				_add_state_nodes(child);
			}
		}
	};

	_add_state_nodes(this);
}

void FiniteStateMachineComponent::_change_state(const StringName& p_new_state_name) {
	if (curr_state) {
		curr_state->exit();
	}

	curr_state = states.get(p_new_state_name);
	curr_state->enter();
}

void FiniteStateMachineComponent::on_input(const Ref<InputEvent>& p_event) {
	if (curr_state) {
		StringName new_state_name = curr_state->on_input(p_event);
		if (!new_state_name.is_empty()) {
			_change_state(new_state_name);
		}
	}
}

void FiniteStateMachineComponent::on_process(double p_delta) {
	if (curr_state) {
		StringName new_state_name = curr_state->on_process(p_delta);
		if (!new_state_name.is_empty()) {
			_change_state(new_state_name);
		}
	}
}

void FiniteStateMachineComponent::on_physics_process(double p_delta) {
	if (curr_state) {
		StringName new_state_name = curr_state->on_physics_process(p_delta);
		if (!new_state_name.is_empty()) {
			_change_state(new_state_name);
		}
	}
}
