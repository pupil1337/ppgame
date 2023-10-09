#ifndef PLAYERGROUNDBASESTATE_H
#define PLAYERGROUNDBASESTATE_H

#include "finiteStateMachine/state.h"

class PlayerGroundBaseState : public State {
	GDCLASS(PlayerGroundBaseState, State)

public:
	virtual void enter() override;
	virtual void exit() override;
	virtual StringName on_input(const Ref<InputEvent> &p_event) override;
	virtual StringName on_process(float deltaTime) override;
	virtual StringName on_physics_process(float deltaTime) override;

//~Begin This Class
	Vector2 input_dir = Vector2(0.0f, 0.0f);
};

#endif // PLAYERGROUNDBASESTATE_H
