#ifndef LEVEL_H
#define LEVEL_H

#include <godot_cpp/classes/node.hpp>
#include <godot_cpp/classes/wrapped.hpp>
using namespace godot;

class Level : public Node {
	GDCLASS(Level, Node)
	typedef Node super;

	// ------------------------------------------

public:
	virtual void _ready() override;

protected:
	static void _bind_methods() {}
};

#endif // LEVEL_H
