#ifndef COMPONENT_H
#define COMPONENT_H

#include "godot_cpp/classes/node.hpp"
#include "godot_cpp/classes/wrapped.hpp"
using namespace godot;

class Component : public Node {
	GDCLASS(Component, Node)

public:
	virtual void InitializeComponent() = 0;

protected:
	static void _bind_methods() {}
};

#endif // COMPONENT_H
