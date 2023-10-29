#include "finiteStateMachineComponent.h"

#include <scene/2d/animated_sprite_2d.h>
#include "state.h"

void FiniteStateMachineComponent::_notification(int p_notification) {
	switch (p_notification) {
		case NOTIFICATION_READY: {
			_add_state_nodes(this);
		} break;
	}
}

void FiniteStateMachineComponent::_add_state_nodes(Node* node) {
	for (int i = 0; i < node->get_child_count(true); ++i) {
		Node* child = node->get_child(i, true);
		if (State* state = Object::cast_to<State>(child)) {
			states[child->get_class_name()] = state;
		} else {
			_add_state_nodes(child);
		}
	}
}

void FiniteStateMachineComponent::on_owner_ready() {
	pre_owner_ready();

	ERR_FAIL_NULL_EDMSG(curr_state, String(get_parent()->get_name()) + "'" + String(get_name()) + " not set start state");
	StringName start_state_name = curr_state->get_class_name();
	curr_state = nullptr;
	_change_state(start_state_name);
}

void FiniteStateMachineComponent::_change_state(const StringName& new_state_name) {
	ERR_FAIL_COND_EDMSG(!states.has(new_state_name), String(get_parent()->get_name()) + "'" + String(get_name()) + " not has state: " + String(new_state_name));

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

