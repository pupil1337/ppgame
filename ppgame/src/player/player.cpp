#include "player.h"

#include <scene/2d/animated_sprite_2d.h>
#include "finiteStateMachine/finiteStateMachine.h"

Player::Player() {

}

void Player::_bind_methods() {
	// finite state machine
	ClassDB::bind_method(D_METHOD("set_finite_state_machine", "fsm"), &Player::set_finite_state_machine);
	ClassDB::bind_method(D_METHOD("get_finite_state_machine"), &Player::get_finite_state_machine);
	ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "finite_state_machine", PROPERTY_HINT_NODE_TYPE, "FiniteStateMachine"), "set_finite_state_machine", "get_finite_state_machine");

	// animated sprite
	ClassDB::bind_method(D_METHOD("set_anim_sprite", "anim_sprite"), &Player::set_anim_sprite);
	ClassDB::bind_method(D_METHOD("get_anim_sprite"), &Player::get_anim_sprite);
	ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "animated_sprite", PROPERTY_HINT_NODE_TYPE, "AnimatedSprite2D"), "set_anim_sprite", "get_anim_sprite");
}

void Player::_notification(int p_notification) {
	switch (p_notification) {
		case NOTIFICATION_READY: {
			set_process(true);
			set_physics_process(true);
			set_process_unhandled_input(true);

			_ready();
		} break;

		case NOTIFICATION_PROCESS: {
			_process(get_process_delta_time());
		} break;

		case NOTIFICATION_PHYSICS_PROCESS: {
			_physics_process(get_physics_process_delta_time());
		} break;
	}
}

void Player::_ready() {
	ERR_FAIL_NULL_EDMSG(fsm, String(get_name()) + " fsm is not set in editor");
	fsm->on_ready();
}

void Player::unhandled_input(const Ref<InputEvent> &p_event) {
	CharacterBody2D::unhandled_input(p_event);

	if (fsm) {
		fsm->on_input(p_event);
	}
}

void Player::_process(float deltaTime) {
	if (fsm) {
		fsm->on_process(deltaTime);
	}
}

void Player::_physics_process(float deltaTime) {
	if (fsm) {
		fsm->on_physics_process(deltaTime);
	}
}

// setting --------------------------------------------------------------------
void Player::set_finite_state_machine(FiniteStateMachine* p_fsm) {
	ERR_MAIN_THREAD_GUARD;
	fsm = p_fsm;
}

FiniteStateMachine* Player::get_finite_state_machine() const {
	ERR_READ_THREAD_GUARD_V(nullptr);
	return fsm;
}

void Player::set_anim_sprite(AnimatedSprite2D *p_animSprite) {
	ERR_MAIN_THREAD_GUARD;
	anim_sprite = p_animSprite;
}

AnimatedSprite2D* Player::get_anim_sprite() const {
	ERR_READ_THREAD_GUARD_V(nullptr)
	return anim_sprite;
}

