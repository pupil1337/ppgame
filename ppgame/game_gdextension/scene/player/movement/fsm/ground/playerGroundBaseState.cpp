#include "playerGroundBaseState.h"

#include "scene/player/movement/fsm/playerMovementFSMComponent.h"
#include "scene/player/movement/playerMovementComponent.h"
#include "scene/player/player.h"

StringName PlayerGroundBaseState::on_physics_process(float deltaTime) {
	PlayerMovementStateBase::on_physics_process(deltaTime);

	if (!fsm->player->is_on_floor()) {
		fsm->player->movement->apply_gravity(deltaTime);
	}

	return StringName();
}
