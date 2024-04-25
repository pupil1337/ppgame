#include "world.h"

#include <godot_cpp/classes/node.hpp>
#include <godot_cpp/classes/packed_scene.hpp>
#include <godot_cpp/classes/ref.hpp>
#include <godot_cpp/classes/resource_loader.hpp>
#include <godot_cpp/variant/utility_functions.hpp>

void World::_ready() {
	ResourceLoader* loader = ResourceLoader::get_singleton();
	loader->load_threaded_request("res://level/level0.tscn");
	// a->load_threaded_request("res://level/level0.tscn");
}

void World::_process(double delta) {
	ResourceLoader* loader = ResourceLoader::get_singleton();
	// UtilityFunctions::print("load status: ", loader->load_threaded_get_status("res://level/level0.tscn"));
	if (loader->load_threaded_get_status("res://level/level0.tscn") == ResourceLoader::ThreadLoadStatus::THREAD_LOAD_LOADED) {
		Ref<PackedScene> a = loader->load_threaded_get("res://level/level0.tscn");
		Node* level = a->instantiate();
		add_child(level);
	} else {
		UtilityFunctions::print("load status: ", loader->load_threaded_get_status("res://level/level0.tscn"));
	}
}
