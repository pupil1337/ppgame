#ifndef PLAYERIDLESTATE_H
#define PLAYERIDLESTATE_H

using namespace godot;

#include "playerGroundBaseState.h"

class PlayerIdleState : public PlayerGroundBaseState {
	GDCLASS(PlayerIdleState, PlayerGroundBaseState)

public:
	virtual void enter() override;
	virtual StringName on_physics_process(float deltaTime) override;
};

#endif // PLAYERIDLESTATE_H
