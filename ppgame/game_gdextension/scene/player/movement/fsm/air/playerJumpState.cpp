#include "playerJumpState.h"

#include "scene/player/movement/fsm/playerMovementFSMComponent.h"
#include "scene/player/movement/playerMovementComponent.h"
#include "scene/player/player.h"

void PlayerJumpState::enter() {
	PlayerAirBaseState::enter();

	fsm->player->movement_component->jump();
	// todo
	// if (fsm) {
	// 	if (fsm->info.anim_sprite) {
	// 		fsm->info.anim_sprite->play("Jump");
	// 	}
	// }
}

StringName PlayerJumpState::on_physics_process(float deltaTime) {
	PlayerAirBaseState::on_physics_process(deltaTime);

	fsm->player->movement_component->move();

	if (fsm->player->movement_component->is_falling()) {
		return StringName("PlayerFallState");
	}

	return StringName();
}
