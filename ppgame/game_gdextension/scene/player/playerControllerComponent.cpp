#include "playerControllerComponent.h"

void PlayerControllerComponent::_bind_methods() {
	PP_ADD_PROPERTY(Variant::VECTOR2, input_dir, PROPERTY_HINT_NONE);
}

void PlayerControllerComponent::_enter_tree() {
	PP_CONTINUE_IF_GAME
}

void PlayerControllerComponent::_ready() {
	PP_CONTINUE_IF_GAME

	set_physics_process(get_multiplayer_authority() == get_multiplayer()->get_unique_id());
}

void PlayerControllerComponent::_process(double delta) {
	PP_CONTINUE_IF_GAME
}

void PlayerControllerComponent::_physics_process(double delta) {
	PP_CONTINUE_IF_GAME

	input_dir = Input::get_singleton()->get_vector("left", "right", "up", "down");
}

void PlayerControllerComponent::_exit_tree() {
	PP_CONTINUE_IF_GAME
}
