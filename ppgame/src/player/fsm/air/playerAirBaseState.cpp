#include "playerAirBaseState.h"

#include "finiteStateMachine/finiteStateMachineComponent.h"
#include "player/movement/playerMovementComponent.h"

void PlayerAirBaseState::enter() {
}

void PlayerAirBaseState::exit() {
}

StringName PlayerAirBaseState::on_input(const Ref<InputEvent> &p_event) {
	return StringName();
}

StringName PlayerAirBaseState::on_process(float deltaTime) {
	return StringName();
}

StringName PlayerAirBaseState::on_physics_process(float deltaTime) {
	Input* input = Input::get_singleton();
	input_dir = input->get_vector(SNAME("left"), SNAME("right"), SNAME("up"), SNAME("down"));

	if (fsm) {
		if (PlayerMovementComponent* movement = Object::cast_to<PlayerMovementComponent>(fsm->info.movement_component)) {
			movement->apply_gravity(deltaTime);
		}
	}
	return StringName();
}
