#include "player_finite_state_machine_base_component.h"

#include <godot_cpp/classes/engine.hpp>
#include <godot_cpp/classes/object.hpp>

#include "character/player/player_finite_state_machine_component.h"

void PlayerFiniteStateMachineBaseComponent::_notification(int p_what) {
	if (!Engine::get_singleton()->is_editor_hint()) {
		if (p_what == NOTIFICATION_PARENTED) {
			if ((player_fsm_component = Object::cast_to<PlayerFiniteStateMachineComponent>(get_parent()))) {
				player_fsm_component->player_fsms.push_back(this);
			}
		}
	}
}
