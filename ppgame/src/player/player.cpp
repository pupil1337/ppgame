#include "player.h"

#include <scene/animation/animation_player.h>
#include "finiteStateMachine/finiteStateMachineComponent.h"
#include "movement/playerMovementComponent.h"

Player::Player() {

}

void Player::_bind_methods() {
	PP_ADD_PROPERTY(Variant::OBJECT, back_arm, PROPERTY_HINT_NODE_TYPE, "AnimationPlayer");
	PP_ADD_PROPERTY(Variant::OBJECT, leg, PROPERTY_HINT_NODE_TYPE, "AnimationPlayer");
	PP_ADD_PROPERTY(Variant::OBJECT, torso, PROPERTY_HINT_NODE_TYPE, "AnimationPlayer");
	PP_ADD_PROPERTY(Variant::OBJECT, head, PROPERTY_HINT_NODE_TYPE, "AnimationPlayer");

	PP_ADD_PROPERTY(Variant::OBJECT, front_arm, PROPERTY_HINT_NODE_TYPE, "AnimationPlayer");
	PP_ADD_PROPERTY(Variant::OBJECT, fsm, PROPERTY_HINT_NODE_TYPE, "FiniteStateMachineComponent");
	PP_ADD_PROPERTY(Variant::OBJECT, movement_component, PROPERTY_HINT_NODE_TYPE, "PlayerMovementComponent");
}

void Player::_notification(int p_notification) {
	switch (p_notification) {
		case NOTIFICATION_READY: {
			set_process(true);
			set_physics_process(true);
			set_process_unhandled_input(true);

			if (!Engine::get_singleton()->is_editor_hint()) {
				_ready();
			}
		} break;

		case NOTIFICATION_PROCESS: {
			if (!Engine::get_singleton()->is_editor_hint()) {
				_process(get_process_delta_time());
			}
		} break;

		case NOTIFICATION_PHYSICS_PROCESS: {
			if (!Engine::get_singleton()->is_editor_hint()) {
				_physics_process(get_physics_process_delta_time());
			}
		} break;
	}
}

void Player::_ready() {
	fsm->on_owner_ready();
}

void Player::unhandled_input(const Ref<InputEvent> &p_event) {
	CharacterBody2D::unhandled_input(p_event);

	fsm->on_input(p_event);
}

void Player::_process(float deltaTime) {
	fsm->on_process(deltaTime);

	// anim_sprite->set_flip_h(movement_component->get_facing_dir().x < 0.0f); todo
}

void Player::_physics_process(float deltaTime) {
	fsm->on_physics_process(deltaTime);
}
