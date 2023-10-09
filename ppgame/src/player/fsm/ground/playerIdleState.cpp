#include "playerIdleState.h"

#include <scene/2d/animated_sprite_2d.h>
#include "finiteStateMachine/finiteStateMachineComponent.h"
#include "player/movement/playerMovementComponent.h"
#include "player/player.h"

void PlayerIdleState::enter() {
	if (fsm) {
		if (fsm->info.anim_sprite) {
			fsm->info.anim_sprite->play("Idle");
		}
	}
}

void PlayerIdleState::exit() {
}

StringName PlayerIdleState::on_input(const Ref<InputEvent> &p_event) {
	PlayerGroundBaseState::on_input(p_event);

	return StringName();
}

StringName PlayerIdleState::on_process(float deltaTime) {
	PlayerGroundBaseState::on_process(deltaTime);

	return StringName();
}

StringName PlayerIdleState::on_physics_process(float deltaTime) {
	PlayerGroundBaseState::on_physics_process(deltaTime);

	if (fsm) {
		if (PlayerMovementComponent* movement = Object::cast_to<PlayerMovementComponent>(fsm->info.movement_component)) {
			movement->move();
		}

		if (Player* player = Object::cast_to<Player>(fsm->info.owner)) {
			if (player->is_on_floor() && !Math::is_zero_approx(input_dir.x)) {
				return String("PlayerRunState");
			}
		}
	}

	return StringName();
}

