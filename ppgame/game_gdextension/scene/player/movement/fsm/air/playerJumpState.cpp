#include "playerJumpState.h"

#include "scene/player/movement/fsm/playerMovementFSMComponent.h"
#include "scene/player/movement/playerMovementComponent.h"
#include "scene/player/player.h"

void PlayerJumpState::enter() {
	PlayerAirBaseState::enter();

	ERR_FAIL_NULL(fsm);
	Player* player = fsm->get_player();
	ERR_FAIL_NULL(player);
	PlayerMovementComponent* movement = player->get_movement();
	ERR_FAIL_NULL(movement);

	movement->jump();
	// todo
	// if (fsm) {
	// 	if (fsm->info.anim_sprite) {
	// 		fsm->info.anim_sprite->play("Jump");
	// 	}
	// }
}

StringName PlayerJumpState::on_physics_process(float deltaTime) {
	PlayerAirBaseState::on_physics_process(deltaTime);

	ERR_FAIL_NULL_V(fsm, StringName());
	Player* player = fsm->get_player();
	ERR_FAIL_NULL_V(player, StringName());
	PlayerMovementComponent* movement = player->get_movement();
	ERR_FAIL_NULL_V(movement, StringName());

	movement->move();

	if (movement->is_falling()) {
		return StringName("PlayerFallState");
	}

	return StringName();
}
