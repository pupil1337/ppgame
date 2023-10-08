#include "playerRunState.h"

#include <scene/2d/animated_sprite_2d.h>
#include "finiteStateMachine/finiteStateMachine.h"

void PlayerRunState::enter() {
	if (fsm) {
		if (fsm->info.anim_sprite) {
			fsm->info.anim_sprite->play("Run");
		}
	}
}

void PlayerRunState::exit() {
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
	
	return StringName();
}

