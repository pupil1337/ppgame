#include "player.h"

#include <godot_cpp/classes/character_body2d.hpp>

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
