#ifndef FINITESTATEMACHINE_H
#define FINITESTATEMACHINE_H

#include <scene/main/node.h>

class String;
class State;

class FiniteStateMachine : public Node {
	GDCLASS(FiniteStateMachine, Node)

protected:
	void _notification(int p_notification);

//~Begin This Class
private:
	void _ready();
	
	void _initialize_state_nodes(Node* node);

	void _process(float deltaTime);

	void _physics_process(float deltaTime);

	HashMap<String, State*> states;
};

#endif // FINITESTATEMACHINE_H
