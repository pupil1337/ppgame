#include "playerMovementFSMComponent.h"

#include <godot_cpp/classes/input.hpp>

#include "scene/player/player.h"
#include "scene/player/movement/fsm/playerMovementStateBase.h"

void PlayerMovementFSMComponent::pre_owner_ready() {
	FiniteStateMachineComponent::pre_owner_ready();

	ERR_FAIL_COND_EDMSG(!states.has(StringName("PlayerIdleState")), String(get_parent()->get_name()) + "'" + String(get_name()) + " not has state: PlayerIdleState");
	curr_state = states.get(StringName("PlayerIdleState"));
	for (HashMap<StringName, State*>::Iterator it = states.begin(); it != states.end(); ++it) {
		if (PlayerMovementStateBase* state = Object::cast_to<PlayerMovementStateBase>(it->value)) {
			state->fsm = this;
		}
	}

	player = Object::cast_to<Player>(get_parent());
}

void PlayerMovementFSMComponent::pre_physics_process(float deltaTime) {
	FiniteStateMachineComponent::pre_physics_process(deltaTime);

	input_dir = Input::get_singleton()->get_vector("left", "right", "up", "down");
}
