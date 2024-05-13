#ifndef LEVEL_H
#define LEVEL_H

#include <cstdint>
#include <godot_cpp/classes/global_constants.hpp>
#include <godot_cpp/classes/node.hpp>
#include <godot_cpp/classes/wrapped.hpp>
#include <godot_cpp/variant/packed_string_array.hpp>
using namespace godot;

class Door;

class Level : public Node {
	GDCLASS(Level, Node)

public:
	int32_t get_camera_limit(Side p_side);

	// ------------------------------------------

public:
	virtual PackedStringArray _get_configuration_warnings() const override;

protected:
	static void _bind_methods() {}
};

#endif // LEVEL_H
