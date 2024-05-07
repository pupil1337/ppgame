#include "level.h"

#include <cstdint>
#include <godot_cpp/classes/global_constants.hpp>
#include <godot_cpp/classes/marker2d.hpp>
#include <godot_cpp/core/error_macros.hpp>
#include <godot_cpp/variant/vector2.hpp>

int32_t Level::get_camera_limit(Side p_side) {
	Marker2D* camera_marker = nullptr;
	if (p_side == Side::SIDE_LEFT || p_side == Side::SIDE_TOP) {
		camera_marker = get_node<Marker2D>("CameraLT");
	} else {
		camera_marker = get_node<Marker2D>("CameraRB");
	}

	ERR_FAIL_NULL_V_EDMSG(camera_marker, p_side == Side::SIDE_LEFT || p_side == Side::SIDE_TOP ? -10000000 : 10000000, "Check level camera marker created");

	Vector2 origin = camera_marker->get_transform().get_origin();
	if (p_side == Side::SIDE_LEFT) {
		return origin.x;
	} else if (p_side == Side::SIDE_TOP) {
		return origin.y;
	} else if (p_side == Side::SIDE_RIGHT) {
		return origin.x;
	} else {
		return origin.y;
	}
}
