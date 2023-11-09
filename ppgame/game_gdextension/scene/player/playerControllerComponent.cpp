#include "playerControllerComponent.h"

#include "system/multiplayerSystem.h"

void PlayerControllerComponent::_ready() {
	PP_CONTINUE_IF_GAME

	set_physics_process(MultiplayerSystem::get_unique_id() == get_multiplayer_authority());
}

void PlayerControllerComponent::_physics_process(double delta) {
	PP_CONTINUE_IF_GAME

	input_dir = Input::get_singleton()->get_vector("left", "right", "up", "down");
}
