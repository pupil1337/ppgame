#include "playerIdleState.h"

void PlayerIdleState::enter() {
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

