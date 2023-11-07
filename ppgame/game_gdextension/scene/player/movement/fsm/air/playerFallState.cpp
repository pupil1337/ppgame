#include "playerFallState.h"

#include "scene/player/movement/fsm/playerMovementFSMComponent.h"
#include "scene/player/movement/playerMovementComponent.h"
#include "scene/player/player.h"

void PlayerFallState::enter() {
	PlayerAirBaseState::enter();

	// todo
	// if (fsm) {
	// 	if (fsm->info.anim_sprite) {
	// 		fsm->info.anim_sprite->play("Fall");
	// 	}
	// }
}

StringName PlayerFallState::on_physics_process(float deltaTime) {
	PlayerAirBaseState::on_physics_process(deltaTime);

	fsm->player->movement_component->move();

	if (fsm->player->is_on_floor()) {
		fsm->player->movement_component->decelerate_horizontally(deltaTime);
		if (Math::is_zero_approx(fsm->input_dir.x)) {
			return StringName("PlayerIdleState");
		} else {
			return StringName("PlayerRunState");
		}
	}

	return StringName();
}
