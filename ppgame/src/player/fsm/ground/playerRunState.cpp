#include "playerRunState.h"

#include <scene/2d/animated_sprite_2d.h>
#include "finiteStateMachine/finiteStateMachineComponent.h"
#include "player/movement/playerMovementComponent.h"

void PlayerRunState::enter() {
	PlayerGroundBaseState::enter();

	if (fsm) {
		if (fsm->info.anim_sprite) {
			fsm->info.anim_sprite->play("Run");
		}
	}
}

void PlayerRunState::exit() {
	PlayerGroundBaseState::exit();
}

StringName PlayerRunState::on_input(const Ref<InputEvent> &p_event) {
	PlayerGroundBaseState::on_input(p_event);

	return StringName();
}

StringName PlayerRunState::on_process(float deltaTime) {
	PlayerGroundBaseState::on_process(deltaTime);

	return StringName();
}

StringName PlayerRunState::on_physics_process(float deltaTime) {
	PlayerGroundBaseState::on_physics_process(deltaTime);

	if (fsm) {
		if (PlayerMovementComponent* movement = Object::cast_to<PlayerMovementComponent>(fsm->info.movement_component)) {
			if (Math::is_zero_approx(input_dir.x)) {
				movement->decelerate_horizontally(deltaTime);
				movement->move();
				return StringName("PlayerIdleState");
			} else {
				movement->accelerate_horizontally(input_dir, deltaTime);
				movement->move();
			}
		}
	}

	Input* input = Input::get_singleton();
	if (input->is_action_just_pressed(SNAME("jump"))) {
		return StringName("PlayerJumpState");
	}

	return StringName();
}

