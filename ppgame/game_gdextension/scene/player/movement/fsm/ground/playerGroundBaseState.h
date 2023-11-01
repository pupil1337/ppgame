#ifndef PLAYERGROUNDBASESTATE_H
#define PLAYERGROUNDBASESTATE_H

using namespace godot;

#include "scene/player/movement/fsm/playerMovementStateBase.h"

class PlayerGroundBaseState : public PlayerMovementStateBase {
	GDCLASS(PlayerGroundBaseState, PlayerMovementStateBase)

public:
	virtual StringName on_physics_process(float deltaTime) override;
};

#endif // PLAYERGROUNDBASESTATE_H
