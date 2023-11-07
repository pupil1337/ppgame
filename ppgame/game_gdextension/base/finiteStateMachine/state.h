#ifndef STATE_H
#define STATE_H

using namespace godot;

class State : public Node {
	GDCLASS(State, Node)

protected:
	static void _bind_methods() {}

	//~Begin This Class
public:
	virtual void enter(){};
	virtual void exit(){};
	virtual StringName on_input(const Ref<InputEvent>& p_event) { return StringName(); };
	virtual StringName on_process(float deltaTime) { return StringName(); };
	virtual StringName on_physics_process(float deltaTime) { return StringName(); };
};

#endif // STATE_H
