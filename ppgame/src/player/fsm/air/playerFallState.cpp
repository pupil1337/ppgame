#include "playerFallState.h"

#include <scene/2d/animated_sprite_2d.h>
#include "finiteStateMachine/finiteStateMachineComponent.h"
#include "player/movement/playerMovementComponent.h"
#include "player/player.h"

void PlayerFallState::enter() {
	PlayerAirBaseState::enter();

	if (fsm) {
		if (fsm->info.anim_sprite) {
			fsm->info.anim_sprite->play("Fall");
		}
	}
}

void PlayerFallState::exit() {
	PlayerAirBaseState::exit();
}

StringName PlayerFallState::on_input(const Ref<InputEvent> &p_event) {
	PlayerAirBaseState::on_input(p_event);

	return StringName();
}

StringName PlayerFallState::on_process(float deltaTime) {
	PlayerAirBaseState::on_process(deltaTime);

	return StringName();
}

StringName PlayerFallState::on_physics_process(float deltaTime) {
	PlayerAirBaseState::on_physics_process(deltaTime);

	if (fsm) {
		if (PlayerMovementComponent* movement = Object::cast_to<PlayerMovementComponent>(fsm->info.movement_component)) {
			movement->move();

			if (Player* player = Object::cast_to<Player>(fsm->info.owner)) {
				if (player->is_on_floor()) {
					movement->decelerate_horizontally(deltaTime);
					if (Math::is_zero_approx(input_dir.x)) {
						return StringName("PlayerIdleState");
					} else {
						return StringName("PlayerRunState");
					}
				}
			}
		}
	}
	return StringName();
}
