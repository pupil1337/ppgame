#ifndef PLAYERIDLESTATE_H
#define PLAYERIDLESTATE_H

#include "playerGroundBaseState.h"

#include "pp.h"

using namespace godot;

class PlayerIdleState : public PlayerGroundBaseState {
	GDCLASS(PlayerIdleState, PlayerGroundBaseState)

protected:
	static void _bind_methods() {}

public:
	virtual void enter() override;
	virtual StringName on_physics_process(float deltaTime) override;
};

#endif // PLAYERIDLESTATE_H
