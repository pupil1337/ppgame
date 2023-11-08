#ifndef FINITESTATEMACHINECOMPONENT_H
#define FINITESTATEMACHINECOMPONENT_H

using namespace godot;

class State;

class FiniteStateMachineComponent : public Node {
	GDCLASS(FiniteStateMachineComponent, Node)

protected:
	static void _bind_methods() {}

	// ------------------------------------------

public:
	virtual void _ready() override;

private:
	void _add_state_nodes(Node* node);
	void _change_state(const StringName& new_state_name);

protected:
	virtual void pre_owner_ready(){};
	virtual void pre_process(float deltaTime){};
	virtual void pre_physics_process(float deltaTime){};

public:
	void on_owner_ready();
	void on_input(const Ref<InputEvent>& p_event);
	void on_process(float deltaTime);
	void on_physics_process(float deltaTime);

protected:
	State* curr_state = nullptr;
	HashMap<StringName, State*> states; // className2state
};

#endif // FINITESTATEMACHINECOMPONENT_H
