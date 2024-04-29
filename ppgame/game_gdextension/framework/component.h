#ifndef COMPONENT_H
#define COMPONENT_H

#include <godot_cpp/classes/node.hpp>
#include <godot_cpp/classes/wrapped.hpp>
using namespace godot;

class Actor;

class Component : public Node {
	GDCLASS(Component, Node)

protected:
	Actor* actor = nullptr;

private:
	void _register_component(Node* p_node);

	// ------------------------------------------

public:
	virtual void _enter_tree() override;

protected:
	static void _bind_methods() {}
};

#endif // COMPONENT_H
