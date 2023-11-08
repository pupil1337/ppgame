#ifndef PLAYERCONTROLLERCOMPONENT_H
#define PLAYERCONTROLLERCOMPONENT_H

using namespace godot;

class PlayerControllerComponent : public Node {
	GDCLASS(PlayerControllerComponent, Node)

protected:
	static void _bind_methods();

private:
	MultiplayerSynchronizer* synchronizer = nullptr;

	// replicates
	Vector2 input_dir;

public:
	_FORCE_INLINE_ MultiplayerSynchronizer* get_synchronizer() const { return synchronizer; }
	void set_synchronizer(MultiplayerSynchronizer* p_synchronizer);

public:
	_FORCE_INLINE_ Vector2 get_input_dir() const { return input_dir; }
	void set_input_dir(const Vector2& p_input_dir);

	// ------------------------------------------

public:
	virtual void _enter_tree() override;
	virtual void _ready() override;
	virtual void _physics_process(double delta) override;
};

#endif // PLAYERCONTROLLERCOMPONENT_H
