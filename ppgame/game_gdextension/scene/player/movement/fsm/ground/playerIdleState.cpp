#include "playerIdleState.h"

#include "scene/player/movement/fsm/playerMovementFSMComponent.h"
#include "scene/player/movement/playerMovementComponent.h"
#include "scene/player/player.h"

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

	fsm->player->movement_component->move();

	if (fsm->player->is_on_floor() && !Math::is_zero_approx(fsm->input_dir.x)) {
		return StringName("PlayerRunState");
	}

	Input* input = Input::get_singleton();
	if (input->is_action_just_pressed("jump")) {
		return StringName("PlayerJumpState");
	}

	return StringName();
}
