#include "world.h"

#include <godot_cpp/classes/engine.hpp>
#include <godot_cpp/classes/marker2d.hpp>
#include <godot_cpp/classes/object.hpp>
#include <godot_cpp/classes/packed_scene.hpp>
#include <godot_cpp/classes/ref.hpp>
#include <godot_cpp/classes/resource.hpp>
#include <godot_cpp/classes/resource_loader.hpp>
#include <godot_cpp/classes/scene_tree.hpp>
#include <godot_cpp/classes/window.hpp>
#include <godot_cpp/core/memory.hpp>
#include <godot_cpp/variant/callable_method_pointer.hpp>
#include <godot_cpp/variant/string.hpp>

#include "async_loader/async_loader.h"
#include "character/player/player.h"
#include "level/level.h"

static AsyncLoader* async_loader = nullptr;

void World::_notification(int p_what) {
	if (!Engine::get_singleton()->is_editor_hint()) {
		if (p_what == NOTIFICATION_POSTINITIALIZE) {
			async_loader = memnew(AsyncLoader);
		}
		if (p_what == NOTIFICATION_PREDELETE) {
			if (async_loader) {
				memdelete(async_loader);
			}
		}
	}
}

void World::_ready() {
	parent_type::_ready();

	if (!Engine::get_singleton()->is_editor_hint()) {
		AsyncLoader::get_singleton()->instance("res://level/level_0.tscn", callable_mp(this, &self_type::_level_instanced_callback));
	}
}

void World::_level_instanced_callback(Node* p_node) {
	curr_level = Object::cast_to<Level>(p_node);
	add_child(curr_level);

	AsyncLoader::get_singleton()->instance("res://character/player/player.tscn", callable_mp(this, &self_type::_player_instanced_callback));
}

void World::_player_instanced_callback(Node* p_node) {
	player = Object::cast_to<Player>(p_node);
	curr_level->add_child(player);
}

World* World::get_world(Node* p_inside_node) {
	if (p_inside_node->is_inside_tree()) {
		return p_inside_node->get_tree()->get_root()->get_node<World>("World");
	}

	return nullptr;
}

void World::add_level_and_player_tp(Level* p_level, const String& p_player_start) {
	if (player) {
		if (curr_level) {
			curr_level->queue_free();
		}
		curr_level = p_level;
		add_child(curr_level);

		player->reparent(curr_level, false);
		Marker2D* player_start = curr_level->get_node<Marker2D>(p_player_start);
		player->set_position(player_start->get_position());
	}
}
