#include "player.h"

#include <godot_cpp/classes/character_body2d.hpp>

#include "character/player/player_finite_state_machine_component.h"

void Player::_ready() {
	if (PlayerFiniteStateMachineComponent* player_fsm = get_component<PlayerFiniteStateMachineComponent>()) {
		player_fsm->on_start();
	}
}

void Player::_process(double delta) {
	if (PlayerFiniteStateMachineComponent* player_fsm = get_component<PlayerFiniteStateMachineComponent>()) {
		player_fsm->on_process(delta);
	}
}

void Player::_physics_process(double delta) {
	if (PlayerFiniteStateMachineComponent* player_fsm = get_component<PlayerFiniteStateMachineComponent>()) {
		player_fsm->on_physics_process(delta);
	}
}
