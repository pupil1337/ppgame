#include "player_camera_component.h"

#include <godot_cpp/classes/camera2d.hpp>
#include <godot_cpp/classes/engine.hpp>
#include <godot_cpp/classes/global_constants.hpp>
#include <godot_cpp/classes/object.hpp>
#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/core/defs.hpp>
#include <godot_cpp/core/error_macros.hpp>
#include <godot_cpp/core/object.hpp>
#include <godot_cpp/core/property_info.hpp>
#include <godot_cpp/variant/packed_string_array.hpp>
#include <godot_cpp/variant/variant.hpp>

#include "character/player/player.h"
#include "level/level.h"

void PlayerCameraComponent::_enter_tree() {
	parent_type::_enter_tree();

	if (!Engine::get_singleton()->is_editor_hint()) {
		// Camera限制
		if (camera) {
			if (Player* player = static_cast<Player*>(actor)) {
				if (Level* level = Object::cast_to<Level>(player->get_parent())) {
					camera->set_limit(Side::SIDE_LEFT, level->get_camera_limit(Side::SIDE_LEFT));
					camera->set_limit(Side::SIDE_TOP, level->get_camera_limit(Side::SIDE_TOP));
					camera->set_limit(Side::SIDE_RIGHT, level->get_camera_limit(Side::SIDE_RIGHT));
					camera->set_limit(Side::SIDE_BOTTOM, level->get_camera_limit(Side::SIDE_BOTTOM));
				} else {
					ERR_PRINT_ED("Player Must add as Level child");
					camera->set_limit(Side::SIDE_LEFT, -10000000);
					camera->set_limit(Side::SIDE_TOP, -10000000);
					camera->set_limit(Side::SIDE_RIGHT, 10000000);
					camera->set_limit(Side::SIDE_BOTTOM, 10000000);
				}
			}
		}
	}
}

// ----------------------------------------------------------------------------

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

PackedStringArray PlayerCameraComponent::_get_configuration_warnings() const {
	PackedStringArray warnings = parent_type::_get_configuration_warnings();

	if (!camera) {
		warnings.push_back("Not Set Camera");
	}

	return warnings;
}
