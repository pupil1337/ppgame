#include "world.h"

#include <godot_cpp/classes/engine.hpp>
#include <godot_cpp/classes/object.hpp>
#include <godot_cpp/classes/packed_scene.hpp>
#include <godot_cpp/classes/ref.hpp>
#include <godot_cpp/classes/resource.hpp>
#include <godot_cpp/classes/resource_loader.hpp>
#include <godot_cpp/core/memory.hpp>

#include "character/player/player.h"
#include "level/level.h"
#include "world/resource_loader_helper.h"

static ResourceLoaderHelper* resource_loader_helper = nullptr;

void World::_enter_tree() {
	parent_type::_enter_tree();

	if (!Engine::get_singleton()->is_editor_hint()) {
		resource_loader_helper = memnew(ResourceLoaderHelper);
	}
}

void World::_ready() {
	parent_type::_ready();

	if (!Engine::get_singleton()->is_editor_hint()) {
		// Test Level
		ResourceLoaderHelper::get_singleton()->load_threaded_request("res://level/level0.tscn", PackedScene::get_class_static(), [this](ResourceLoader::ThreadLoadStatus p_status, Ref<Resource> p_resource, float p_progress) {
			if (p_status == ResourceLoader::ThreadLoadStatus::THREAD_LOAD_LOADED) {
				PackedScene* packed_level = Object::cast_to<PackedScene>(*p_resource);
				Level* level = Object::cast_to<Level>(packed_level->instantiate());
				add_child(level);

				// Test Player
				ResourceLoaderHelper::get_singleton()->load_threaded_request("res://character/player/player.tscn", PackedScene::get_class_static(), [this](ResourceLoader::ThreadLoadStatus p_status, Ref<Resource> p_resource, float p_progress) {
					if (p_status == ResourceLoader::ThreadLoadStatus::THREAD_LOAD_LOADED) {
						PackedScene* packed_player = Object::cast_to<PackedScene>(*p_resource);
						Player* player = Object::cast_to<Player>(packed_player->instantiate());
						add_child(player);
					}
				});
			}
		});
	}
}

void World::_process(double delta) {
	parent_type::_process(delta);

	if (!Engine::get_singleton()->is_editor_hint()) {
		ResourceLoaderHelper::get_singleton()->flush_queries();
	}
}

void World::_exit_tree() {
	parent_type::_exit_tree();

	if (!Engine::get_singleton()->is_editor_hint()) {
		if (resource_loader_helper) {
			memdelete(resource_loader_helper);
		}
	}
}
