#include "player.h"

#include "scene/player/movement/fsm/playerMovementFSMComponent.h"
#include "scene/player/movement/playerMovementComponent.h"
#include "scene/player/playerControllerComponent.h"

Player::Player() {
}

void Player::_bind_methods() {
	ClassDB::bind_method(D_METHOD(_STR(set_movement_fsm), "movement_fsm"), &self_type::set_movement_fsm);
	ClassDB::bind_method(D_METHOD(_STR(get_movement_fsm)), &self_type::get_movement_fsm);
	ADD_PROPERTY(PropertyInfo(Variant::OBJECT, _STR(movement_fsm), PROPERTY_HINT_NODE_TYPE, "PlayerMovementFSMComponent"), _STR(set_movement_fsm), _STR(get_movement_fsm));

	ClassDB::bind_method(D_METHOD(_STR(set_movement), "movement"), &self_type::set_movement);
	ClassDB::bind_method(D_METHOD(_STR(get_movement)), &self_type::get_movement);
	ADD_PROPERTY(PropertyInfo(Variant::OBJECT, _STR(movement), PROPERTY_HINT_NODE_TYPE, "PlayerMovementComponent"), _STR(set_movement), _STR(get_movement));

	ClassDB::bind_method(D_METHOD(_STR(set_controller), "controller"), &self_type::set_controller);
	ClassDB::bind_method(D_METHOD(_STR(get_controller)), &self_type::get_controller);
	ADD_PROPERTY(PropertyInfo(Variant::OBJECT, _STR(controller), PROPERTY_HINT_NODE_TYPE, "PlayerControllerComponent"), _STR(set_controller), _STR(get_controller));

	ClassDB::bind_method(D_METHOD(_STR(set_uid), "uid"), &self_type::set_uid);
	ClassDB::bind_method(D_METHOD(_STR(get_uid)), &self_type::get_uid);
	ADD_PROPERTY(PropertyInfo(Variant::INT, _STR(uid)), _STR(set_uid), _STR(get_uid));
}

void Player::_ready() {
	PP_CONTINUE_IF_GAME

	if (movement_fsm) {
		movement_fsm->on_owner_ready();
	}
}

void Player::_process(double delta) {
	PP_CONTINUE_IF_GAME

	if (movement_fsm) {
		movement_fsm->on_process(delta);
		// anim_sprite->set_flip_h(movement->get_facing_dir().x < 0.0f); TODO
	}
}

void Player::_physics_process(double delta) {
	PP_CONTINUE_IF_GAME

	if (get_multiplayer()->get_unique_id() == uid) {
		if (movement_fsm) {
			movement_fsm->on_physics_process(delta);
		}
	}
}

void Player::_unhandled_input(const Ref<InputEvent>& p_event) {
	PP_CONTINUE_IF_GAME

	if (movement_fsm) {
		movement_fsm->on_input(p_event);
	}
}

void Player::set_movement_fsm(PlayerMovementFSMComponent* p_movement_fsm) {
	movement_fsm = p_movement_fsm;
}

void Player::set_movement(PlayerMovementComponent* p_movement) {
	movement = p_movement;
}

void Player::set_controller(PlayerControllerComponent* p_controller) {
	controller = p_controller;
}

void Player::set_uid(int32_t p_uid) {
	if (p_uid > 0) {
		uid = p_uid;

		if (controller) {
			controller->set_multiplayer_authority(p_uid);
		}
	}
}
