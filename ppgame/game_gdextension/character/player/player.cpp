#include "player.h"

#include <godot_cpp/classes/animation_player.hpp>
#include <godot_cpp/classes/character_body2d.hpp>
#include <godot_cpp/classes/engine.hpp>
#include <godot_cpp/classes/global_constants.hpp>
#include <godot_cpp/classes/sprite2d.hpp>
#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/core/defs.hpp>
#include <godot_cpp/core/object.hpp>
#include <godot_cpp/core/property_info.hpp>
#include <godot_cpp/variant/variant.hpp>

#include "character/player/player_finite_state_machine_component.h"

void Player::_enter_tree() {
	parent_type::_enter_tree();
}

void Player::_ready() {
	parent_type::_ready();
}

void Player::_process(double delta) {
	parent_type::_process(delta);

	if (!Engine::get_singleton()->is_editor_hint()) {
		if (PlayerFiniteStateMachineComponent* player_fsm = get_component<PlayerFiniteStateMachineComponent>()) {
			player_fsm->on_process(delta);
		}
	}
}

void Player::_physics_process(double delta) {
	parent_type::_physics_process(delta);

	if (!Engine::get_singleton()->is_editor_hint()) {
		if (PlayerFiniteStateMachineComponent* player_fsm = get_component<PlayerFiniteStateMachineComponent>()) {
			player_fsm->on_physics_process(delta);
		}
	}
}

void Player::_exit_tree() {
	parent_type::_exit_tree();
}

Sprite2D* Player::get_sprite() {
	return get_node<Sprite2D>("PlayerSprite");
}

AnimationPlayer* Player::get_animation_player() {
	return get_node<AnimationPlayer>("AnimationPlayer");
}
