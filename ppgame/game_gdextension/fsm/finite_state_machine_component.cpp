#include "finite_state_machine_component.h"

#include <godot_cpp/classes/engine.hpp>
#include <godot_cpp/classes/global_constants.hpp>
#include <godot_cpp/classes/input_event.hpp>
#include <godot_cpp/classes/node.hpp>
#include <godot_cpp/classes/object.hpp>
#include <godot_cpp/classes/ref.hpp>
#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/core/defs.hpp>
#include <godot_cpp/core/error_macros.hpp>
#include <godot_cpp/core/object.hpp>
#include <godot_cpp/core/property_info.hpp>
#include <godot_cpp/variant/string_name.hpp>
#include <godot_cpp/variant/utility_functions.hpp>

#include "fsm/state.h"

void FiniteStateMachineComponent::add_state(State* p_state) {
	states.insert(p_state->get_class(), p_state);
}

void FiniteStateMachineComponent::_change_state(const StringName& p_new_state_name) {
	if (curr_state) {
		curr_state->exit();
	}

	ERR_FAIL_COND_EDMSG(!states.has(p_new_state_name), "FSM: not has this state: " + p_new_state_name);
	curr_state = states.get(p_new_state_name);
	UtilityFunctions::print(get_parent()->get_name(), " state->", p_new_state_name);
	curr_state->enter();
}

void FiniteStateMachineComponent::on_process(double p_delta) {
	if (!Engine::get_singleton()->is_editor_hint()) {
		ERR_FAIL_NULL_EDMSG(curr_state, "FSM: on_process curr_state == nullptr");

		StringName new_state_name = curr_state->on_process(p_delta);
		if (!new_state_name.is_empty()) {
			_change_state(new_state_name);
		}
	}
}

void FiniteStateMachineComponent::on_physics_process(double p_delta) {
	if (!Engine::get_singleton()->is_editor_hint()) {
		ERR_FAIL_NULL_EDMSG(curr_state, "FSM: on_physics_process curr_state == nullptr");

		curr_state->on_physics_process(p_delta);
	}
}

// ----------------------------------------------------------------------------

void FiniteStateMachineComponent::set_curr_state(State* p_curr_state) {
	curr_state = p_curr_state;
}

State* FiniteStateMachineComponent::get_curr_state() {
	return curr_state;
}

void FiniteStateMachineComponent::_bind_methods() {
	// curr_state
	ClassDB::bind_method(D_METHOD(_STR(set_curr_state), _STR(state)), &self_type::set_curr_state);
	ClassDB::bind_method(D_METHOD(_STR(get_curr_state)), &self_type::get_curr_state);
	ADD_PROPERTY(PropertyInfo(Variant::OBJECT, _STR(default_state), PROPERTY_HINT_NODE_TYPE, "State"), _STR(set_curr_state), _STR(get_curr_state));
}
