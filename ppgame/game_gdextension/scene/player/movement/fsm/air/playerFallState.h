#ifndef PLAYERFALLSTATE
#define PLAYERFALLSTATE

using namespace godot;

#include "playerAirBaseState.h"

class PlayerFallState : public PlayerAirBaseState {
	GDCLASS(PlayerFallState, PlayerAirBaseState)

public:
	virtual void enter() override;
	virtual StringName on_physics_process(float deltaTime) override;
};

#endif // PLAYERFALLSTATE
