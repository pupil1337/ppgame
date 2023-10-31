#ifndef PLAYERAIRBASESTATE
#define PLAYERAIRBASESTATE

#include "scene/player/movement/fsm/playerMovementStateBase.h"

#include "pp.h"

using namespace godot;

class PlayerAirBaseState : public PlayerMovementStateBase {
	GDCLASS(PlayerAirBaseState, PlayerMovementStateBase)

protected:
	static void _bind_methods() {}

//~Begin This Class
protected:
	virtual StringName on_physics_process(float deltaTime) override;
};

#endif // PLAYERAIRBASESTATE
