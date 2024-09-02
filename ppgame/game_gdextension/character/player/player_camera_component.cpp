#include "player_camera_component.h"

#include <godot_cpp/classes/camera2d.hpp>
#include <godot_cpp/classes/engine.hpp>
#include <godot_cpp/classes/global_constants.hpp>
#include <godot_cpp/classes/object.hpp>

#include "character/player/player.h"
#include "level/level.h"

void PlayerCameraComponent::_enter_tree() {
	parent_type::_enter_tree();

	if (!Engine::get_singleton()->is_editor_hint()) {
		// Camera限制
		if (Camera2D* camera = get_camera()) {
			if (Player* player = static_cast<Player*>(actor)) {
				if (Level* level = Object::cast_to<Level>(player->get_parent())) {
					camera->set_limit(Side::SIDE_LEFT, level->get_camera_limit(Side::SIDE_LEFT));
					camera->set_limit(Side::SIDE_TOP, level->get_camera_limit(Side::SIDE_TOP));
					camera->set_limit(Side::SIDE_RIGHT, level->get_camera_limit(Side::SIDE_RIGHT));
					camera->set_limit(Side::SIDE_BOTTOM, level->get_camera_limit(Side::SIDE_BOTTOM));
				}
			}
		}
	}
}

Camera2D* PlayerCameraComponent::get_camera() {
	return get_node<Camera2D>("../Camera2D");
}
