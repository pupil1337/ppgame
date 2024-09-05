#include "state.h"

#include <godot_cpp/classes/engine.hpp>
#include <godot_cpp/core/error_macros.hpp>

#include "fsm/finite_state_machine_component.h"
#include "utils/node_utils.h"

void State::_notification(int p_what) {
	if (!Engine::get_singleton()->is_editor_hint()) {
		if (p_what == NOTIFICATION_PARENTED) {
			owner_fsm = NodeUtils::get_parent_node<FiniteStateMachineComponent>(this);
			if (!owner_fsm || !owner_fsm->add_state(this)) {
				ERR_PRINT_ED("_register_state->" + get_class());
			}
		}
	}
}
