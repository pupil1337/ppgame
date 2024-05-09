#ifndef LEVEL_H
#define LEVEL_H

#include <cstdint>
#include <godot_cpp/classes/global_constants.hpp>
#include <godot_cpp/classes/marker2d.hpp>
#include <godot_cpp/classes/node2d.hpp>
#include <godot_cpp/classes/wrapped.hpp>
#include <godot_cpp/templates/vector.hpp>
#include <godot_cpp/variant/packed_string_array.hpp>
#include <godot_cpp/variant/string.hpp>
using namespace godot;

class Door;

class Level : public Node2D {
	GDCLASS(Level, Node2D)

	friend Door;

public:
	int32_t get_camera_limit(Side p_side);
	Vector<String> get_link_level_paths();

private:
	Vector<Door*> doors;

	// ------------------------------------------

public:
	virtual void _ready() override;
	virtual PackedStringArray _get_configuration_warnings() const override;

protected:
	static void _bind_methods() {}
};

#endif // LEVEL_H
