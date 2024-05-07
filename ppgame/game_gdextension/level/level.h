#ifndef LEVEL_H
#define LEVEL_H

#include <cstdint>
#include <godot_cpp/classes/global_constants.hpp>
#include <godot_cpp/classes/marker2d.hpp>
#include <godot_cpp/classes/node2d.hpp>
#include <godot_cpp/classes/wrapped.hpp>
#include <godot_cpp/variant/packed_string_array.hpp>
using namespace godot;

class Level : public Node2D {
	GDCLASS(Level, Node2D)

public:
	int32_t get_camera_limit(Side p_side);

	// ------------------------------------------

protected:
	static void _bind_methods() {}
};

#endif // LEVEL_H
