#ifndef PLAYERCONTROLLERCOMPONENT_H
#define PLAYERCONTROLLERCOMPONENT_H

using namespace godot;

class PlayerControllerComponent : public Node {
	GDCLASS(PlayerControllerComponent, Node)

protected:
	static void _bind_methods();

public:
	virtual void _enter_tree() override;
	virtual void _ready() override;
	virtual void _process(double delta) override;
	virtual void _physics_process(double delta) override;
	virtual void _exit_tree() override;

	//~Begin This Class
public:
	PP_PROPERTY(Vector2, input_dir);
};

#endif // PLAYERCONTROLLERCOMPONENT_H
