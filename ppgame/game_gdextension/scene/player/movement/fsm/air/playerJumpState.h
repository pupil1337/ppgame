#ifndef PLAYERJUMPSTATE
#define PLAYERJUMPSTATE

using namespace godot;

#include "playerAirBaseState.h"

class PlayerJumpState : public PlayerAirBaseState {
	GDCLASS(PlayerJumpState, PlayerAirBaseState)

public:
	virtual void enter() override;
	virtual StringName on_physics_process(float deltaTime) override;
};

#endif // PLAYERJUMPSTATE
