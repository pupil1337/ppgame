#include "player_camera_component.h"

#include <godot_cpp/classes/camera2d.hpp>
#include <godot_cpp/classes/global_constants.hpp>
#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/core/defs.hpp>
#include <godot_cpp/core/object.hpp>
#include <godot_cpp/core/property_info.hpp>
#include <godot_cpp/variant/variant.hpp>

void PlayerCameraComponent::set_camera(Camera2D* p_camera) {
	camera = p_camera;
}

Camera2D* PlayerCameraComponent::get_camera() {
	return camera;
}

void PlayerCameraComponent::_bind_methods() {
	// camera
	ClassDB::bind_method(D_METHOD(_STR(set_camera), _STR(camera)), &self_type::set_camera);
	ClassDB::bind_method(D_METHOD(_STR(get_camera)), &self_type::get_camera);
	ADD_PROPERTY(PropertyInfo(Variant::OBJECT, _STR(camera), godot::PROPERTY_HINT_NODE_TYPE, "Camera2D"), _STR(set_camera), _STR(get_camera));
}
