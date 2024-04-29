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
