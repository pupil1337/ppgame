#include "playerGroundBaseState.h"

#include "finiteStateMachine/finiteStateMachineComponent.h"
#include "player/movement/playerMovementComponent.h"
#include "player/player.h"

void PlayerGroundBaseState::enter() {
}

void PlayerGroundBaseState::exit() {
}

StringName PlayerGroundBaseState::on_input(const Ref<InputEvent> &p_event) {
	return StringName();
}

StringName PlayerGroundBaseState::on_process(float deltaTime) {
	return StringName();
}

StringName PlayerGroundBaseState::on_physics_process(float deltaTime) {
	Input* input = Input::get_singleton();
	input_dir = input->get_vector("left", "right", "up", "down");

	if (fsm) {
		if (Player* player = Object::cast_to<Player>(fsm->info.owner)) {
			if (!player->is_on_floor()) {
				if (PlayerMovementComponent* movement = Object::cast_to<PlayerMovementComponent>(fsm->info.movement_component)) {
					movement->apply_gravity(deltaTime);
				}
			}
		}
	}

	return StringName();
}

