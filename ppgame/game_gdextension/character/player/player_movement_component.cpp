#include "player_movement_component.h"

#include "character/player/player_input_component.h"
#include "framework/actor.h"

void PlayerMovementComponent::_ready() {
	if (actor) {
		player_input_component = actor->get_component<PlayerInputComponent>();
	}
}

void PlayerMovementComponent::_process(double delta) {
}

void PlayerMovementComponent::_physics_process(double delta) {
}
