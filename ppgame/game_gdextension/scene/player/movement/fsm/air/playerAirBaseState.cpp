#include "playerAirBaseState.h"

#include "scene/player/movement/fsm/playerMovementFSMComponent.h"
#include "scene/player/movement/playerMovementComponent.h"
#include "scene/player/player.h"

StringName PlayerAirBaseState::on_physics_process(float deltaTime) {
	PlayerMovementStateBase::on_physics_process(deltaTime);

	fsm->player->movement->apply_gravity(deltaTime);

	return StringName();
}
