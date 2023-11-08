#ifndef PP_H
#define PP_H

// ----------------------------------------------------------------------------
// godot-cpp
// ----------------------------------------------------------------------------

// gdextension
#include <gdextension_interface.h>

// gen
// - classes
#include <godot_cpp/classes/animation_player.hpp>
#include <godot_cpp/classes/button.hpp>
#include <godot_cpp/classes/camera2d.hpp>
#include <godot_cpp/classes/character_body2d.hpp>
#include <godot_cpp/classes/control.hpp>
#include <godot_cpp/classes/e_net_connection.hpp>
#include <godot_cpp/classes/e_net_multiplayer_peer.hpp>
#include <godot_cpp/classes/engine.hpp>
#include <godot_cpp/classes/input.hpp>
#include <godot_cpp/classes/input_event.hpp>
#include <godot_cpp/classes/multiplayer_api.hpp>
#include <godot_cpp/classes/multiplayer_peer.hpp>
#include <godot_cpp/classes/multiplayer_synchronizer.hpp>
#include <godot_cpp/classes/node.hpp>
#include <godot_cpp/classes/packed_scene.hpp>
#include <godot_cpp/classes/resource_loader.hpp>
#include <godot_cpp/classes/scene_tree.hpp>
#include <godot_cpp/classes/window.hpp>
// - core
// - variant
#include <godot_cpp/variant/string_name.hpp>
#include <godot_cpp/variant/utility_functions.hpp>

// include
// - classes
#include <godot_cpp/classes/ref.hpp>
// - core
#include <godot_cpp/core/class_db.hpp>
// - templates
#include <godot_cpp/templates/hash_map.hpp>
#include <godot_cpp/templates/vector.hpp>
// - variant

/**
 * 如果是Game则继续执行，否则return
 */
#define PP_CONTINUE_IF_GAME                          \
	if (Engine::get_singleton()->is_editor_hint()) { \
		return;                                      \
	}

#endif // PP_H
