#ifndef PLAYERGROUNDBASESTATE_H
#define PLAYERGROUNDBASESTATE_H

#include "scene/player/movement/fsm/playerMovementStateBase.h"

#include "pp.h"

using namespace godot;

class PlayerGroundBaseState : public PlayerMovementStateBase {
	GDCLASS(PlayerGroundBaseState, PlayerMovementStateBase)

protected:
	static void _bind_methods() {}

public:
	virtual StringName on_physics_process(float deltaTime) override;
};

#endif // PLAYERGROUNDBASESTATE_H
