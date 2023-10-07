#ifndef FINITESTATEMACHINE_H
#define FINITESTATEMACHINE_H

#include <scene/main/node.h>

class StringName;
class State;
class AnimatedSprite2D;

class FiniteStateMachine : public Node {
	GDCLASS(FiniteStateMachine, Node)

protected:
	void _notification(int p_notification);

	static void _bind_methods();

//~Begin This Class
private:
	void _ready();

private:
	void _add_state_nodes(Node* node);
	void _change_state(const StringName& new_state_name);

public:
	// call from owner
	void on_input(const Ref<InputEvent> &p_event);
	void on_process(float deltaTime);
	void on_physics_process(float deltaTime);

private:
	// setting
	void set_curr_state(State* p_state);
	State* get_curr_state() const;
	void set_anim_sprite(AnimatedSprite2D* p_animSprite);
	AnimatedSprite2D* get_anim_sprite() const;
	
	AnimatedSprite2D* anim_sprite = nullptr;

	State* curr_state = nullptr;
	HashMap<StringName, State*> states;// className2state
};

#endif // FINITESTATEMACHINE_H
