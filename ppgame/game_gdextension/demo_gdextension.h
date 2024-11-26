#ifndef DEMO_GDEXTENSION_H
#define DEMO_GDEXTENSION_H

#include <godot_cpp/classes/node2d.hpp>
#include <godot_cpp/classes/wrapped.hpp>
using namespace godot;

class DemoGdextension : public Node2D {
	GDCLASS(DemoGdextension, Node2D)

public:
	virtual void _ready() override;
	virtual void _process(double delta) override;

protected:
	static void _bind_methods() {}
};

#endif // DEMO_GDEXTENSION_H
