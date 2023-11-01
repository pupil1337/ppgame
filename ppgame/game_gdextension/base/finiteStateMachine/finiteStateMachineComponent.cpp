#include "finiteStateMachineComponent.h"

#include "state.h"

void FiniteStateMachineComponent::_ready() {
	PP_CONTINUE_IF_GAME
	_add_state_nodes(this);
}

void FiniteStateMachineComponent::_add_state_nodes(Node* node) {
	for (int i = 0; i < node->get_child_count(true); ++i) {
		Node* child = node->get_child(i, true);
		if (State* state = Object::cast_to<State>(child)) {
			ERR_FAIL_COND_EDMSG(states.has(child->get_class()), "fsm has same name state");
			states[child->get_class()] = state;
		} else {
			_add_state_nodes(child);
		}
	}
}

void FiniteStateMachineComponent::on_owner_ready() {
	pre_owner_ready();

	ERR_FAIL_NULL_EDMSG(curr_state, "fsm not set default state in pre_owner_ready()");
	StringName start_state_name = curr_state->get_class();
	curr_state = nullptr;
	_change_state(start_state_name);
}

void FiniteStateMachineComponent::_change_state(const StringName& new_state_name) {
	ERR_FAIL_COND_EDMSG(!states.has(new_state_name), String("fsm not has this state: ") + String(new_state_name));

	if (curr_state) {
		curr_state->exit();
	}

	curr_state = states.get(new_state_name);
	curr_state->enter();
}

void FiniteStateMachineComponent::on_input(const Ref<InputEvent> &p_event) {
	if (curr_state) {
		String new_state_name = curr_state->on_input(p_event);
		if (!new_state_name.is_empty()) {
			_change_state(new_state_name);
		}
	}
}

void FiniteStateMachineComponent::on_process(float deltaTime) {
	pre_process(deltaTime);

	if (curr_state) {
		String new_state_name = curr_state->on_process(deltaTime);
		if (!new_state_name.is_empty()) {
			_change_state(new_state_name);
		}
	}
}


void FiniteStateMachineComponent::on_physics_process(float deltaTime) {
	pre_physics_process(deltaTime);

	if (curr_state) {
		String new_state_name = curr_state->on_physics_process(deltaTime);
		if (!new_state_name.is_empty()) {
			_change_state(new_state_name);
		}
	}
}

