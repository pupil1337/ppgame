#ifndef STATE_H
#define STATE_H

#include <scene/main/node.h>

class FiniteStateMachine;
class AnimatedSprite2D;

class State : public Node {
	GDCLASS(State, Node)

	friend FiniteStateMachine;

//~Begin This Class
public:
	virtual void enter() = 0;

	virtual void exit() = 0;

	virtual StringName on_input(const Ref<InputEvent> &p_event) = 0;

	virtual StringName on_process(float deltaTime) = 0;

	virtual StringName on_physics_process(float deltaTime) = 0;

protected:
	FiniteStateMachine* fsm = nullptr;
};

#endif // STATE_H
