#ifndef PLAYERIDLESTATE_H
#define PLAYERIDLESTATE_H

#include "playerGroundBaseState.h"

class PlayerIdleState : public PlayerGroundBaseState {
	GDCLASS(PlayerIdleState, PlayerGroundBaseState)

public:
	virtual void enter() override;
	virtual void exit() override;
	virtual StringName on_input(const Ref<InputEvent> &p_event) override;
	virtual StringName on_process(float deltaTime) override;
	virtual StringName on_physics_process(float deltaTime) override;
};

#endif // PLAYERIDLESTATE_H
