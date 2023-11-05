#ifndef WORLD_H
#define WORLD_H

using namespace godot;

class World : public Node {
	GDCLASS(World, Node)

protected:
	static void _bind_methods() {}

public:
	virtual void _enter_tree() override;
	virtual void _ready() override;
	virtual void _exit_tree() override;

//~Begin This Class
private:
	void _add_player(int32_t uid);
	void _del_player(int32_t uid);
};

#endif // WORLD_H
