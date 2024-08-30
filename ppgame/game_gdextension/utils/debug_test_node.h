#ifndef DEBUG_TEST_NODE_H
#define DEBUG_TEST_NODE_H

#include <godot_cpp/classes/node.hpp>
#include <godot_cpp/classes/wrapped.hpp>
#include <godot_cpp/variant/packed_string_array.hpp>
using namespace godot;

class DebugTestNode : public Node {
	GDCLASS(DebugTestNode, Node)

public:
	DebugTestNode() {}

	// ------------------------------------------

public:
	virtual void _process(double p_delta) override;
	virtual void _physics_process(double p_delta) override;
	virtual void _enter_tree() override;
	virtual void _exit_tree() override;
	virtual void _ready() override;
	virtual PackedStringArray _get_configuration_warnings() const override;

protected:
	static void _bind_methods() {}
	void _notification(int p_what);
};

#endif // DEBUG_TEST_NODE_H
