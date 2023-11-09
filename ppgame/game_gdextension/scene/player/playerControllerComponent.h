#ifndef PLAYERCONTROLLERCOMPONENT_H
#define PLAYERCONTROLLERCOMPONENT_H

using namespace godot;

class PlayerControllerComponent : public Node {
	GDCLASS(PlayerControllerComponent, Node)

protected:
	static void _bind_methods() {}

	// ------------------------------------------

public:
	virtual void _ready() override;
	virtual void _physics_process(double delta) override;

public:
	_FORCE_INLINE_ Vector2 get_input_dir() const { return input_dir; }

private:
	Vector2 input_dir;
};

#endif // PLAYERCONTROLLERCOMPONENT_H
