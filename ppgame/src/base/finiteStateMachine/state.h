#ifndef STATE_H
#define STATE_H

#include <scene/main/node.h>

class FiniteStateMachineComponent;
class AnimatedSprite2D;

class State : public Node {
	GDCLASS(State, Node)

//~Begin This Class
public:
	virtual void enter() { };
	virtual void exit() { };
	virtual StringName on_input(const Ref<InputEvent> &p_event) { return StringName(); };
	virtual StringName on_process(float deltaTime) { return StringName(); };
	virtual StringName on_physics_process(float deltaTime) { return StringName(); };
};

#endif // STATE_H
