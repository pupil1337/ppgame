#ifndef FINITESTATEMACHINE_H
#define FINITESTATEMACHINE_H

#include <scene/main/node.h>

class FiniteStateMachine : public Node {
	GDCLASS(FiniteStateMachine, Node)

protected:
	void _notification(int p_notification);
};

#endif // FINITESTATEMACHINE_H