#ifndef PLAYERMOVEMENTFSMCOMPONENT_H
#define PLAYERMOVEMENTFSMCOMPONENT_H

using namespace godot;

#include "base/finiteStateMachine/finiteStateMachineComponent.h"

class Player;

class PlayerMovementFSMComponent : public FiniteStateMachineComponent {
	GDCLASS(PlayerMovementFSMComponent, FiniteStateMachineComponent);

protected:
	virtual void pre_owner_ready() override;
	virtual void pre_physics_process(float deltaTime) override;

	//~Begin This Class
public:
	Player* player = nullptr;
	Vector2 input_dir = Vector2(0.0f, 0.0f);
};

#endif // PLAYERMOVEMENTFSMCOMPONENT_H
