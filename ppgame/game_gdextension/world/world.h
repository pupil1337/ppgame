#ifndef WORLD_H
#define WORLD_H

#include <godot_cpp/classes/node.hpp>
#include <godot_cpp/classes/wrapped.hpp>
#include <godot_cpp/templates/vector.hpp>
#include <godot_cpp/variant/string.hpp>
using namespace godot;

class Level;

class World : public Node {
	GDCLASS(World, Node)

private:
	void _level_instanced_callback(Node* p_node);

private:
	Level* curr_level = nullptr;
	Vector<Level*> loaded_levels;

	// ------------------------------------------

public:
	virtual void _enter_tree() override;
	virtual void _exit_tree() override;
	virtual void _ready() override;
	virtual void _process(double delta) override;

protected:
	static void _bind_methods() {}
};

#endif // WORLD_H
