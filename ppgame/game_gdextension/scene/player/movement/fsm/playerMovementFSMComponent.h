#ifndef PLAYERMOVEMENTFSMCOMPONENT_H
#define PLAYERMOVEMENTFSMCOMPONENT_H

using namespace godot;

#include "base/finiteStateMachine/finiteStateMachineComponent.h"

class Player;

class PlayerMovementFSMComponent : public FiniteStateMachineComponent {
	GDCLASS(PlayerMovementFSMComponent, FiniteStateMachineComponent);

protected:
	static void _bind_methods();

private:
	Player* player = nullptr;

public:
	_FORCE_INLINE_ Player* get_player() const { return player; }
	void set_player(Player* p_player);

	// ------------------------------------------

protected:
	virtual void pre_owner_ready() override;
};

#endif // PLAYERMOVEMENTFSMCOMPONENT_H
