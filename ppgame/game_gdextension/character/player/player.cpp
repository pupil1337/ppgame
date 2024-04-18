#include "player.h"

#include <godot_cpp/classes/animation_player.hpp>
#include <godot_cpp/classes/character_body2d.hpp>
#include <godot_cpp/classes/global_constants.hpp>
#include <godot_cpp/classes/sprite2d.hpp>
#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/core/defs.hpp>
#include <godot_cpp/core/object.hpp>
#include <godot_cpp/core/property_info.hpp>
#include <godot_cpp/variant/variant.hpp>

#include "character/player/player_finite_state_machine_component.h"

void Player::_ready() {
	super::_ready();
}

void Player::_process(double delta) {
	super::_process(delta);

	if (PlayerFiniteStateMachineComponent* player_fsm = get_component<PlayerFiniteStateMachineComponent>()) {
		player_fsm->on_process(delta);
	}
}

void Player::_physics_process(double delta) {
	super::_physics_process(delta);

	if (PlayerFiniteStateMachineComponent* player_fsm = get_component<PlayerFiniteStateMachineComponent>()) {
		player_fsm->on_physics_process(delta);
	}
}

void Player::set_sprite(Sprite2D* p_sprite) {
	sprite = p_sprite;
}

Sprite2D* Player::get_sprite() {
	return sprite;
}

void Player::set_animation_player(AnimationPlayer* p_animation_player) {
	animation_player = p_animation_player;
}

AnimationPlayer* Player::get_animation_player() {
	return animation_player;
}

void Player::_bind_methods() {
	// sprite
	ClassDB::bind_method(D_METHOD(_STR(set_sprite), _STR(sprite)), &self_type::set_sprite);
	ClassDB::bind_method(D_METHOD(_STR(get_sprite)), &self_type::get_sprite);
	ADD_PROPERTY(PropertyInfo(Variant::OBJECT, _STR(sprite), PROPERTY_HINT_NODE_TYPE, "Sprite2D"), _STR(set_sprite), _STR(get_sprite));

	// animation_player
	ClassDB::bind_method(D_METHOD(_STR(set_animation_player), _STR(animation_player)), &self_type::set_animation_player);
	ClassDB::bind_method(D_METHOD(_STR(get_animation_player)), &self_type::get_animation_player);
	ADD_PROPERTY(PropertyInfo(Variant::OBJECT, _STR(animation_player), PROPERTY_HINT_NODE_TYPE, "AnimationPlayer"), _STR(set_animation_player), _STR(get_animation_player));
}
