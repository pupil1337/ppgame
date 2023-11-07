#include "playerRunState.h"

#include "scene/player/movement/fsm/playerMovementFSMComponent.h"
#include "scene/player/movement/playerMovementComponent.h"
#include "scene/player/player.h"

void PlayerRunState::enter() {
	PlayerGroundBaseState::enter();

	// todo
	// if (fsm) {
	// 	if (fsm->info.anim_sprite) {
	// 		fsm->info.anim_sprite->play("Run");
	// 	}
	// }
}

StringName PlayerRunState::on_physics_process(float deltaTime) {
	PlayerGroundBaseState::on_physics_process(deltaTime);

	if (Math::is_zero_approx(fsm->input_dir.x)) {
		fsm->player->movement->decelerate_horizontally(deltaTime);
		fsm->player->movement->move();
		return StringName("PlayerIdleState");
	} else {
		fsm->player->movement->accelerate_horizontally(fsm->input_dir, deltaTime);
		fsm->player->movement->move();
	}

	Input* input = Input::get_singleton();
	if (input->is_action_just_pressed("jump")) {
		return StringName("PlayerJumpState");
	}

	return StringName();
}
