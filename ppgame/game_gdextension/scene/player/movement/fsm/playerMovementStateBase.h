#ifndef PLAYERMOVEMENTSTATEBASE_H
#define PLAYERMOVEMENTSTATEBASE_H

using namespace godot;

#include "base/finiteStateMachine/state.h"

class PlayerMovementFSMComponent;

class PlayerMovementStateBase : public State {
	GDCLASS(PlayerMovementStateBase, State)

//~Begin This Class
public:
	PlayerMovementFSMComponent* fsm = nullptr;
};

#endif // PLAYERMOVEMENTSTATEBASE_H
