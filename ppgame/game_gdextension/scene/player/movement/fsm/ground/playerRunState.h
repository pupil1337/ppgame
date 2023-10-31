#ifndef PLAYERRUNSTATE_H
#define PLAYERRUNSTATE_H

#include "playerGroundBaseState.h"

#include "pp.h"

class PlayerRunState : public PlayerGroundBaseState {
	GDCLASS(PlayerRunState, PlayerGroundBaseState)

public:
	virtual void enter() override;
	virtual StringName on_physics_process(float deltaTime) override;
};

#endif // PLAYERRUNSTATE_H
