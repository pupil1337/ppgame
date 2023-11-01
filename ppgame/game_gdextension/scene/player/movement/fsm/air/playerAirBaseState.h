#ifndef PLAYERAIRBASESTATE
#define PLAYERAIRBASESTATE

using namespace godot;

#include "scene/player/movement/fsm/playerMovementStateBase.h"

class PlayerAirBaseState : public PlayerMovementStateBase {
	GDCLASS(PlayerAirBaseState, PlayerMovementStateBase)

protected:
	virtual StringName on_physics_process(float deltaTime) override;
};

#endif // PLAYERAIRBASESTATE
