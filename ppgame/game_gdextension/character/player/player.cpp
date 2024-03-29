#include "player.h"

#include <godot_cpp/classes/animated_sprite2d.hpp>
#include <godot_cpp/classes/engine.hpp>
#include <godot_cpp/classes/input_event.hpp>
#include <godot_cpp/classes/ref.hpp>

#include "character/player/fsm/player_finite_state_machine_component.h"
#include "character/player/player_movement_component.h"

void Player::_ready() {
	animated_sprite2d = get_node<AnimatedSprite2D>("AnimatedSprite2D");
	player_movement_component = get_node<PlayerMovementComponent>("PlayerMovementComponent");
	player_finite_state_machine_component = get_node<PlayerFiniteStateMachineComponent>("PlayerFiniteStateMachineComponent");

	if (!Engine::get_singleton()->is_editor_hint()) {
		if (player_finite_state_machine_component) {
			player_finite_state_machine_component->InitializeComponent();
		}
	}
}

void Player::_unhandled_key_input(const Ref<InputEvent>& p_event) {
	if (player_finite_state_machine_component) {
		player_finite_state_machine_component->on_input(p_event);
	}
}

void Player::_bind_methods() {
}
