#ifndef DOOR_H
#define DOOR_H

#include <godot_cpp/classes/area2d.hpp>
#include <godot_cpp/classes/node2d.hpp>
#include <godot_cpp/classes/wrapped.hpp>
using namespace godot;

class Door : public Area2D {
	GDCLASS(Door, Area2D)

private:
	void _body_entered(Node2D* p_body);

public:
	Door();

	// ------------------------------------------

public:
	virtual void _enter_tree() override;

protected:
	static void _bind_methods() {}
};

#endif // DOOR_H
