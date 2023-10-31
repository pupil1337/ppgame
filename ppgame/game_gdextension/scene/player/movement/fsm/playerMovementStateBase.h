#ifndef PLAYERMOVEMENTSTATEBASE_H
#define PLAYERMOVEMENTSTATEBASE_H

#include "base/finiteStateMachine/state.h"

#include "pp.h"

using namespace godot;

class PlayerMovementFSMComponent;

class PlayerMovementStateBase : public State {
	GDCLASS(PlayerMovementStateBase, State)

protected:
	static void _bind_methods() {}

//~Begin This Class
public:
	PlayerMovementFSMComponent* fsm = nullptr;
};

#endif // PLAYERMOVEMENTSTATEBASE_H
