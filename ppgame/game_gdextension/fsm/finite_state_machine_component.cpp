#include "finite_state_machine_component.h"

#include <godot_cpp/classes/engine.hpp>
#include <godot_cpp/core/error_macros.hpp>
#include <godot_cpp/variant/string_name.hpp>
#include <godot_cpp/variant/utility_functions.hpp>

#include "concurrent_state_machine_component.h"
#include "fsm/state.h"
#include "utils/node_utils.h"

void FiniteStateMachineComponent::_notification(int p_what) {
	if (!Engine::get_singleton()->is_editor_hint()) {
		if (p_what == NOTIFICATION_PARENTED) {
			if ((owner_csm_component = NodeUtils::get_parent_node<ConcurrentStateMachineComponent>(this))) {
				owner_csm_component->fsms.push_back(this);
			}
		}
	}
}

bool FiniteStateMachineComponent::add_state(State* p_state) {
	ERR_FAIL_NULL_V_EDMSG(p_state, false, get_class() + " add a nullptr state");
	ERR_FAIL_COND_V_EDMSG(states.has(p_state->get_class()), false, get_class() + " try re-add state->" + p_state->get_class());
	states.insert(p_state->get_class(), p_state);
	if (p_state->is_default_state) {
		if (!curr_state) {
			curr_state = p_state;
		} else {
			WARN_PRINT_ED(curr_state->get_class() + " is default state, but " + p_state->get_class() + " is also default.");
		}
	}
	return true;
}

void FiniteStateMachineComponent::on_start() {
	ERR_FAIL_NULL_EDMSG(curr_state, "FSM: on_start curr_state == nullptr");

	curr_state->enter();
}

void FiniteStateMachineComponent::_change_state(const StringName& p_new_state_name) {
	if (curr_state) {
		curr_state->exit();
	}

	ERR_FAIL_COND_EDMSG(!states.has(p_new_state_name), "FSM: not has this state: " + p_new_state_name);
	curr_state = states.get(p_new_state_name);
	UtilityFunctions::print(get_class(), " state->", p_new_state_name);
	curr_state->enter();
}

void FiniteStateMachineComponent::on_process(double p_delta) {
	ERR_FAIL_NULL_EDMSG(curr_state, "FSM: on_process curr_state == nullptr");

	StringName new_state_name = curr_state->on_process(p_delta);
	if (!new_state_name.is_empty()) {
		_change_state(new_state_name);
	}
}

void FiniteStateMachineComponent::on_physics_process(double p_delta) {
	ERR_FAIL_NULL_EDMSG(curr_state, "FSM: on_physics_process curr_state == nullptr");

	curr_state->on_physics_process(p_delta);
}

void FiniteStateMachineComponent::on_input(int p_fsm_input, const Variant& p_variant) {
	ERR_FAIL_NULL_EDMSG(curr_state, "FSM: on_input curr_state == nullptr");

	StringName new_state_name = curr_state->on_input(p_fsm_input, p_variant);
	if (!new_state_name.is_empty()) {
		_change_state(new_state_name);
	}
}
