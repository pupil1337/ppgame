#include "playerControllerComponent.h"

void PlayerControllerComponent::_bind_methods() {
	// synchronizer
	ClassDB::bind_method(D_METHOD(_STR(set_synchronizer), _STR(synchronizer)), &self_type::set_synchronizer);
	ClassDB::bind_method(D_METHOD(_STR(get_synchronizer)), &self_type::get_synchronizer);
	ADD_PROPERTY(PropertyInfo(Variant::OBJECT, _STR(synchronizer), PROPERTY_HINT_NODE_TYPE, "MultiplayerSynchronizer"), _STR(set_synchronizer), _STR(get_synchronizer));

	// input_dir
	ClassDB::bind_method(D_METHOD(_STR(set_input_dir), _STR(input_dir)), &self_type::set_input_dir);
	ClassDB::bind_method(D_METHOD(_STR(get_input_dir)), &self_type::get_input_dir);
	ADD_PROPERTY(PropertyInfo(Variant::VECTOR2, _STR(input_dir)), _STR(set_input_dir), _STR(get_input_dir));
}

void PlayerControllerComponent::set_synchronizer(MultiplayerSynchronizer* p_synchronizer) {
	synchronizer = p_synchronizer;
}

void PlayerControllerComponent::set_input_dir(const Vector2& p_input_dir) {
	input_dir = p_input_dir;
}

// ----------------------------------------------------------------------------

void PlayerControllerComponent::_enter_tree() {
	PP_CONTINUE_IF_GAME

	ERR_FAIL_NULL(synchronizer);
	synchronizer->set_visibility_for(1, true);
}

void PlayerControllerComponent::_ready() {
	PP_CONTINUE_IF_GAME

	set_physics_process(get_multiplayer_authority() == get_multiplayer()->get_unique_id());
}

void PlayerControllerComponent::_physics_process(double delta) {
	PP_CONTINUE_IF_GAME

	input_dir = Input::get_singleton()->get_vector("left", "right", "up", "down");
}
