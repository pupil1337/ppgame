#include "playerAirBaseState.h"

#include "scene/player/movement/fsm/playerMovementFSMComponent.h"
#include "scene/player/movement/playerMovementComponent.h"
#include "scene/player/player.h"

StringName PlayerAirBaseState::on_physics_process(float deltaTime) {
	PlayerMovementStateBase::on_physics_process(deltaTime);

	ERR_FAIL_NULL_V(fsm, StringName());
	Player* player = fsm->get_player();
	ERR_FAIL_NULL_V(player, StringName());
	PlayerMovementComponent* movement = player->get_movement();
	ERR_FAIL_NULL_V(movement, StringName());

	movement->apply_gravity(deltaTime);

	return StringName();
}
