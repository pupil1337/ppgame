#ifndef PLAYERMOVEMENTSTATEBASE_H
#define PLAYERMOVEMENTSTATEBASE_H

#include "base/finiteStateMachine/state.h"

class PlayerMovementFSMComponent;

class PlayerMovementStateBase : public State {

//~Begin This Class
public:
	PlayerMovementFSMComponent* fsm = nullptr;
};

#endif // PLAYERMOVEMENTSTATEBASE_H
