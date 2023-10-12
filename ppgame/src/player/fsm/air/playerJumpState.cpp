#include "playerJumpState.h"

#include <scene/2d/animated_sprite_2d.h>
#include "finiteStateMachine/finiteStateMachineComponent.h"
#include "player/movement/playerMovementComponent.h"

void PlayerJumpState::enter() {
	PlayerAirBaseState::enter();

	if (fsm) {
		if (fsm->info.anim_sprite) {
			fsm->info.anim_sprite->play("Jump");
		}

		if (PlayerMovementComponent* movement = Object::cast_to<PlayerMovementComponent>(fsm->info.movement_component)) {
			movement->jump();
		}
	}
}

void PlayerJumpState::exit() {
	PlayerAirBaseState::exit();
}

StringName PlayerJumpState::on_input(const Ref<InputEvent> &p_event) {
	PlayerAirBaseState::on_input(p_event);

	return StringName();
}

StringName PlayerJumpState::on_process(float deltaTime) {
	PlayerAirBaseState::on_process(deltaTime);

	return StringName();
}

StringName PlayerJumpState::on_physics_process(float deltaTime) {
	PlayerAirBaseState::on_physics_process(deltaTime);

	if (fsm) {
		if (PlayerMovementComponent* movement = Object::cast_to<PlayerMovementComponent>(fsm->info.movement_component)) {
			movement->move();

			if (movement->is_falling()) {
				return StringName("PlayerFallState");
			}
		}
	}

	return StringName();
}
