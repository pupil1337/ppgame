#ifndef FINITESTATEMACHINE_H
#define FINITESTATEMACHINE_H

#include <scene/main/node.h>

class StringName;
class State;
class AnimatedSprite2D;

class FiniteStateMachine : public Node {
	GDCLASS(FiniteStateMachine, Node)

protected:
	static void _bind_methods();
	void _notification(int p_notification);

//~Begin This Class
private:
	void _add_state_nodes(Node* node);
	void _change_state(const StringName& new_state_name);

public:
	// call from owner
	void on_ready();
	void on_input(const Ref<InputEvent> &p_event);
	void on_process(float deltaTime);
	void on_physics_process(float deltaTime);

	struct Info {
		Node* owner = nullptr;
		AnimatedSprite2D* anim_sprite = nullptr;
	} info;

private:
	// setting
	void set_curr_state(State* p_state);
	State* get_curr_state() const;

	State* curr_state = nullptr;
	HashMap<StringName, State*> states;// className2state
};

#endif // FINITESTATEMACHINE_H
