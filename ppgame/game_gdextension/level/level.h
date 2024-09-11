#ifndef LEVEL_H
#define LEVEL_H

#include <cstdint>
#include <godot_cpp/classes/global_constants.hpp>
#include <godot_cpp/classes/node.hpp>
#include <godot_cpp/classes/wrapped.hpp>
#include <godot_cpp/variant/packed_string_array.hpp>
#include <godot_cpp/variant/packed_vector2_array.hpp>
using namespace godot;

class Door;

//! 关卡
class Level : public Node {
	GDCLASS(Level, Node)

public:
	//! 获取摄像机视野限制
	/*!
	 * \param p_side 方向
	 */
	int32_t get_camera_limit(Side p_side);

	//! 获取导航形状
	PackedVector2Array get_navigation_mesh_polygon();

public:
	Level() {}

	// ------------------------------------------

public:
	virtual PackedStringArray _get_configuration_warnings() const override;

protected:
	static void _bind_methods() {}
};

#endif // LEVEL_H
