#ifndef WORLD_H
#define WORLD_H

#include <godot_cpp/classes/node.hpp>
#include <godot_cpp/classes/wrapped.hpp>
using namespace godot;

class World : public Node {
	GDCLASS(World, Node)
	typedef Node super;

	// ------------------------------------------

public:
	virtual void _ready() override;
	virtual void _process(double delta) override;

protected:
	static void _bind_methods() {}
};

#endif // WORLD_H
