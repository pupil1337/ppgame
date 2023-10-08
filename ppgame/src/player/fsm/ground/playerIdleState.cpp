#include "playerIdleState.h"

#include <scene/2d/animated_sprite_2d.h>
#include "finiteStateMachine/finiteStateMachineComponent.h"

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

	return StringName();
}

