#include "level.h"
#include "godot_cpp/classes/object.hpp"

#include <cstdint>
#include <godot_cpp/classes/global_constants.hpp>
#include <godot_cpp/classes/marker2d.hpp>
#include <godot_cpp/core/error_macros.hpp>
#include <godot_cpp/variant/packed_string_array.hpp>
#include <godot_cpp/variant/transform2d.hpp>
#include <godot_cpp/variant/vector2.hpp>

int32_t Level::get_camera_limit(Side p_side) {
	Marker2D* camera_marker = nullptr;
	if (p_side == Side::SIDE_LEFT || p_side == Side::SIDE_TOP) {
		camera_marker = get_node<Marker2D>("CameraLT");
	} else {
		camera_marker = get_node<Marker2D>("CameraRB");
	}

	if (camera_marker) {
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

	ERR_PRINT_ED("Level: " + get_name() + " not cameraLT or cameraRB");
	if (p_side == Side::SIDE_LEFT) {
		return -10000000;
	} else if (p_side == Side::SIDE_TOP) {
		return -10000000;
	} else if (p_side == Side::SIDE_RIGHT) {
		return 10000000;
	} else {
		return 10000000;
	}
}

PackedStringArray Level::_get_configuration_warnings() const {
	PackedStringArray ret;

	if (Object::cast_to<Marker2D>(get_node_or_null("CameraLT")) == nullptr) {
		ret.push_back("not set CameraLT(Marker2D) Node");
	}

	if (Object::cast_to<Marker2D>(get_node_or_null("CameraRB")) == nullptr) {
		ret.push_back("not set CameraRB(Marker2D) Node");
	}

	return ret;
}
