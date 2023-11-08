#include "playerIdleState.h"

#include "scene/player/movement/fsm/playerMovementFSMComponent.h"
#include "scene/player/movement/playerMovementComponent.h"
#include "scene/player/player.h"
#include "scene/player/playerControllerComponent.h"

void PlayerIdleState::enter() {
	PlayerGroundBaseState::enter();

	// todo
	// if (fsm) {
	// 	if (fsm->info.anim_sprite) {
	// 		fsm->info.anim_sprite->play("Idle");
	// 	}
	// }
}

StringName PlayerIdleState::on_physics_process(float deltaTime) {
	PlayerGroundBaseState::on_physics_process(deltaTime);

	ERR_FAIL_NULL_V(fsm, StringName());
	Player* player = fsm->get_player();
	ERR_FAIL_NULL_V(player, StringName());
	PlayerControllerComponent* controller = player->get_controller();
	ERR_FAIL_NULL_V(controller, StringName());
	PlayerMovementComponent* movement = player->get_movement();
	ERR_FAIL_NULL_V(movement, StringName());

	movement->move();

	if (player->is_on_floor() && !Math::is_zero_approx(controller->get_input_dir().x)) {
		return StringName("PlayerRunState");
	}

	Input* input = Input::get_singleton();
	if (input->is_action_just_pressed("jump")) {
		return StringName("PlayerJumpState");
	}

	return StringName();
}
