#include "player.h"

#include "character/player/fsm/player_finite_state_machine_component.h"
#include "character/player/player_movement_component.h"
#include <godot_cpp/classes/animated_sprite2d.hpp>

void Player::_ready() {
	animated_sprite2d = get_node<AnimatedSprite2D>("AnimatedSprite2D");
	player_movement_component = get_node<PlayerMovementComponent>("PlayerMovementComponent");
	player_finite_state_machine_component = get_node<PlayerFiniteStateMachineComponent>("PlayerFiniteStateMachineComponent");
}

void Player::_input(const Ref<InputEvent>& event) {
}

// void Player::_shortcut_input(const Ref<InputEvent>& event) {
// }

// void Player::_unhandled_input(const Ref<InputEvent>& event) {
// }

// void Player::_unhandled_key_input(const Ref<InputEvent>& event) {
// }

void Player::_bind_methods() {
}
