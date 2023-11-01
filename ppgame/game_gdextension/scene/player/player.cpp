#include "player.h"

#include "scene/player/movement/fsm/playerMovementFSMComponent.h"
#include "scene/player/movement/playerMovementComponent.h"

Player::Player() {

}

void Player::_bind_methods() {
	PP_ADD_PROPERTY(Variant::OBJECT, back_arm, PROPERTY_HINT_NODE_TYPE, "AnimationPlayer");
	PP_ADD_PROPERTY(Variant::OBJECT, leg, PROPERTY_HINT_NODE_TYPE, "AnimationPlayer");
	PP_ADD_PROPERTY(Variant::OBJECT, torso, PROPERTY_HINT_NODE_TYPE, "AnimationPlayer");
	PP_ADD_PROPERTY(Variant::OBJECT, head, PROPERTY_HINT_NODE_TYPE, "AnimationPlayer");

	PP_ADD_PROPERTY(Variant::OBJECT, front_arm, PROPERTY_HINT_NODE_TYPE, "AnimationPlayer");
	PP_ADD_PROPERTY(Variant::OBJECT, movement_fsm_component, PROPERTY_HINT_NODE_TYPE, "FiniteStateMachineComponent");
	PP_ADD_PROPERTY(Variant::OBJECT, movement_component, PROPERTY_HINT_NODE_TYPE, "PlayerMovementComponent");
}

void Player::_ready() {
	PP_CONTINUE_IF_GAME
	if (movement_fsm_component) {
		movement_fsm_component->on_owner_ready();
	}
}

void Player::_process(double delta) {
	PP_CONTINUE_IF_GAME
	if (movement_fsm_component) {
		movement_fsm_component->on_process(delta);
		// anim_sprite->set_flip_h(movement_component->get_facing_dir().x < 0.0f); TODO
	}
}

void Player::_physics_process(double delta) {
	PP_CONTINUE_IF_GAME
	if (movement_fsm_component) {
		movement_fsm_component->on_physics_process(delta);
	}

}

void Player::_unhandled_input(const Ref<InputEvent> &p_event) {
	PP_CONTINUE_IF_GAME
	if (movement_fsm_component) {
		movement_fsm_component->on_input(p_event);
	}
}
