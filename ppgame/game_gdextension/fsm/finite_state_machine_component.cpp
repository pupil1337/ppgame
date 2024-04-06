#include "finite_state_machine_component.h"

#include <godot_cpp/classes/input_event.hpp>
#include <godot_cpp/classes/node.hpp>
#include <godot_cpp/classes/object.hpp>
#include <godot_cpp/classes/ref.hpp>
#include <godot_cpp/core/error_macros.hpp>
#include <godot_cpp/variant/string_name.hpp>

#include "fsm/state.h"

void FiniteStateMachineComponent::add_state(State* p_state) {
	states.insert(p_state->get_class(), p_state);
}

void FiniteStateMachineComponent::on_start(const StringName& p_start_state) {
	ERR_FAIL_COND_EDMSG(curr_state, "FSM has stared, dont twice");

	_change_state(p_start_state);

	ERR_FAIL_COND_EDMSG(!curr_state, "FSM start state: " + p_start_state + " failed");
}

void FiniteStateMachineComponent::_change_state(const StringName& p_new_state_name) {
	if (curr_state) {
		curr_state->exit();
	}

	ERR_FAIL_COND_EDMSG(!states.has(p_new_state_name), "FSM not has this state: " + p_new_state_name);
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
