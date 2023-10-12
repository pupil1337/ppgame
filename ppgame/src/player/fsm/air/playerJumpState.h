#ifndef PLAYERJUMPSTATE
#define PLAYERJUMPSTATE

#include "playerAirBaseState.h"

class PlayerJumpState : public PlayerAirBaseState {
	GDCLASS(PlayerJumpState, PlayerAirBaseState)

public:
	virtual void enter() override;
	virtual void exit() override;
	virtual StringName on_input(const Ref<InputEvent> &p_event) override;
	virtual StringName on_process(float deltaTime) override;
	virtual StringName on_physics_process(float deltaTime) override;
};

#endif // PLAYERJUMPSTATE
