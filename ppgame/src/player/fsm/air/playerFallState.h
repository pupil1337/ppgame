#ifndef PLAYERFALLSTATE
#define PLAYERFALLSTATE

#include "playerAirBaseState.h"

class PlayerFallState : public PlayerAirBaseState {
	GDCLASS(PlayerFallState, PlayerAirBaseState)

public:
	virtual void enter() override;
	virtual void exit() override;
	virtual StringName on_input(const Ref<InputEvent> &p_event) override;
	virtual StringName on_process(float deltaTime) override;
	virtual StringName on_physics_process(float deltaTime) override;
};

#endif // PLAYERFALLSTATE
