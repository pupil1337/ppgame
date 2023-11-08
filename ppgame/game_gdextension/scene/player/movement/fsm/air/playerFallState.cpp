#include "playerFallState.h"

#include "scene/player/movement/fsm/playerMovementFSMComponent.h"
#include "scene/player/movement/playerMovementComponent.h"
#include "scene/player/player.h"
#include "scene/player/playerControllerComponent.h"

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

	ERR_FAIL_NULL_V(fsm, StringName());
	Player* player = fsm->get_player();
	ERR_FAIL_NULL_V(player, StringName());
	PlayerControllerComponent* controller = player->get_controller();
	ERR_FAIL_NULL_V(controller, StringName());
	PlayerMovementComponent* movement = player->get_movement();
	ERR_FAIL_NULL_V(movement, StringName());

	movement->move();

	if (player->is_on_floor()) {
		movement->decelerate_horizontally(deltaTime);
		if (Math::is_zero_approx(controller->get_input_dir().x)) {
			return StringName("PlayerIdleState");
		} else {
			return StringName("PlayerRunState");
		}
	}

	return StringName();
}
