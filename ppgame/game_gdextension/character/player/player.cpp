#include "player.h"

#include <godot_cpp/classes/animation_player.hpp>
#include <godot_cpp/classes/camera2d.hpp>
#include <godot_cpp/classes/character_body2d.hpp>
#include <godot_cpp/classes/engine.hpp>
#include <godot_cpp/classes/global_constants.hpp>
#include <godot_cpp/classes/object.hpp>
#include <godot_cpp/classes/sprite2d.hpp>
#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/core/defs.hpp>
#include <godot_cpp/core/error_macros.hpp>
#include <godot_cpp/core/object.hpp>
#include <godot_cpp/core/property_info.hpp>
#include <godot_cpp/variant/variant.hpp>

#include "level/level.h"

void Player::_enter_tree() {
	parent_type::_enter_tree();

	if (!Engine::get_singleton()->is_editor_hint()) {
		Level* level = Object::cast_to<Level>(get_parent());
		ERR_FAIL_NULL_EDMSG(level, "Player Must add as Level child");

		// Camera限制
		if (Camera2D* camera = get_camera()) {
			camera->set_limit(Side::SIDE_LEFT, level->get_camera_limit(Side::SIDE_LEFT));
			camera->set_limit(Side::SIDE_TOP, level->get_camera_limit(Side::SIDE_TOP));
			camera->set_limit(Side::SIDE_RIGHT, level->get_camera_limit(Side::SIDE_RIGHT));
			camera->set_limit(Side::SIDE_BOTTOM, level->get_camera_limit(Side::SIDE_BOTTOM));
		}
	}
}

void Player::_ready() {
	parent_type::_ready();
}

void Player::_process(double delta) {
	parent_type::_process(delta);
}

void Player::_physics_process(double delta) {
	parent_type::_physics_process(delta);
}

void Player::_exit_tree() {
	parent_type::_exit_tree();
}

Sprite2D* Player::get_sprite() {
	return get_node<Sprite2D>("PlayerSprite");
}

AnimationPlayer* Player::get_animation_player() {
	return get_node<AnimationPlayer>("AnimationPlayer");
}

Camera2D* Player::get_camera() {
	return get_node<Camera2D>("Camera2D");
}
