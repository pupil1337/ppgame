#include "concurrent_state_machine_component.h"

#include <godot_cpp/classes/engine.hpp>
#include <godot_cpp/templates/hash_map.hpp>
#include <godot_cpp/templates/vector.hpp>
#include <godot_cpp/variant/string_name.hpp>
#include <godot_cpp/variant/variant.hpp>

#include "fsm/finite_state_machine_component.h"
#include "fsm/state.h"
#include "fsm/state_condition.h" // IWYU pragma: keep

void ConcurrentStateMachineComponent::_notification(int p_what) {
	if (!Engine::get_singleton()->is_editor_hint()) {
		if (p_what == NOTIFICATION_POSTINITIALIZE) {
			delete condition;
			condition = _new_condition();
		} else if (p_what == NOTIFICATION_PREDELETE) {
			delete condition;
		}
	}
}

void ConcurrentStateMachineComponent::_ready() {
	parent_type::_ready();

	if (!Engine::get_singleton()->is_editor_hint()) {
		Vector<State*> states;
		for (int i = 0; i < fsms.size(); ++i) {
			for (HashMap<StringName, State*>::Iterator it = fsms[i]->states.begin(); it != fsms[i]->states.end(); ++it) {
				states.push_back(it->value);
			}
		}
		_init_those_state_mem(states);

		_update_logic_condition();
		_update_physics_condition();

		for (int i = 0; i < fsms.size(); ++i) {
			if (fsms[i]) {
				fsms[i]->on_start();
			}
		}
	}
}

/*!
 * 先更新逻辑条件, 再更新逻辑帧
 */
void ConcurrentStateMachineComponent::_process(double p_delta) {
	parent_type::_process(p_delta);

	if (!Engine::get_singleton()->is_editor_hint()) {
		_update_logic_condition();
		for (int i = 0; i < fsms.size(); ++i) {
			if (fsms[i]) {
				fsms[i]->on_process(p_delta);
			}
		}
	}
}

/*!
 * 先更新物理帧, 再更新物理条件
 */
void ConcurrentStateMachineComponent::_physics_process(double p_delta) {
	parent_type::_physics_process(p_delta);

	if (!Engine::get_singleton()->is_editor_hint()) {
		for (int i = 0; i < fsms.size(); ++i) {
			if (fsms[i]) {
				fsms[i]->on_physics_process(p_delta);
			}
		}
		_update_physics_condition();
	}
}

void ConcurrentStateMachineComponent::on_input(int p_fsm_input, const Variant& p_variant) {
	for (int i = 0; i < fsms.size(); ++i) {
		if (fsms[i]) {
			fsms[i]->on_input(p_fsm_input, p_variant);
		}
	}

	_update_logic_condition();
	_update_physics_condition();
}
