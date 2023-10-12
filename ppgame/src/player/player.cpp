#include "player.h"

#include <scene/2d/animated_sprite_2d.h>
#include "finiteStateMachine/finiteStateMachineComponent.h"
#include "movement/playerMovementComponent.h"

Player::Player() {

}

void Player::_bind_methods() {
	// finite state machine
	ClassDB::bind_method(D_METHOD("set_finite_state_machine", "fsm"), &Player::set_finite_state_machine);
	ClassDB::bind_method(D_METHOD("get_finite_state_machine"), &Player::get_finite_state_machine);
	ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "finite_state_machine", PROPERTY_HINT_NODE_TYPE, "FiniteStateMachineComponent"), "set_finite_state_machine", "get_finite_state_machine");

	// animated sprite
	ClassDB::bind_method(D_METHOD("set_anim_sprite", "anim_sprite"), &Player::set_anim_sprite);
	ClassDB::bind_method(D_METHOD("get_anim_sprite"), &Player::get_anim_sprite);
	ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "animated_sprite", PROPERTY_HINT_NODE_TYPE, "AnimatedSprite2D"), "set_anim_sprite", "get_anim_sprite");

	// movement component
	ClassDB::bind_method(D_METHOD("set_movement_component", "movement"), &Player::set_movement_component);
	ClassDB::bind_method(D_METHOD("get_movement_component"), &Player::get_movement_component);
	ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "movement_component", PROPERTY_HINT_NODE_TYPE, "PlayerMovementComponent"), "set_movement_component", "get_movement_component");
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

	anim_sprite->set_flip_h(movement_component->get_facing_dir().x < 0.0f);
}

void Player::_physics_process(float deltaTime) {
	fsm->on_physics_process(deltaTime);
}

// setting --------------------------------------------------------------------
void Player::set_finite_state_machine(FiniteStateMachineComponent* p_fsm) {
	ERR_MAIN_THREAD_GUARD;
	fsm = p_fsm;
}

FiniteStateMachineComponent* Player::get_finite_state_machine() const {
	ERR_READ_THREAD_GUARD_V(nullptr);
	return fsm;
}

void Player::set_anim_sprite(AnimatedSprite2D *p_animSprite) {
	ERR_MAIN_THREAD_GUARD;
	anim_sprite = p_animSprite;
}

AnimatedSprite2D* Player::get_anim_sprite() const {
	ERR_READ_THREAD_GUARD_V(nullptr);
	return anim_sprite;
}

void Player::set_movement_component(PlayerMovementComponent *p_movement) {
	ERR_MAIN_THREAD_GUARD;
	movement_component = p_movement;
}

PlayerMovementComponent *Player::get_movement_component() const {
	ERR_READ_THREAD_GUARD_V(nullptr);
	return movement_component;
}
