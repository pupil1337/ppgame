#ifndef WORLD_H
#define WORLD_H

using namespace godot;

class Player;

class World : public Node {
	GDCLASS(World, Node)

protected:
	static void _bind_methods() {}

	// ------------------------------------------

public:
	virtual void _enter_tree() override;
	virtual void _ready() override;
	virtual void _exit_tree() override;

private:
	void _add_player(int32_t uid);
	void _del_player(int32_t uid);

	HashMap<int32_t, Player*> players;
};

#endif // WORLD_H
