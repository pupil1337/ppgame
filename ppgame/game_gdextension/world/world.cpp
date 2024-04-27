#include "world.h"

#include <godot_cpp/classes/ref.hpp>
#include <godot_cpp/classes/resource.hpp>
#include <godot_cpp/core/memory.hpp>
#include <godot_cpp/variant/utility_functions.hpp>

#include "world/resource_loader_helper.h"

static ResourceLoaderHelper* resource_loader_helper = nullptr;

void World::_enter_tree() {
	resource_loader_helper = memnew(ResourceLoaderHelper);
}

void World::_ready() {
	// Test
	ResourceLoaderHelper::get_singleton()->load_threaded_request("res://level/level0.tscn", [](Ref<Resource>) {
		// UtilityFunctions::print("Level0 loaded!!!!!!!!!");
		// add_child(nullptr);
	});

	// Test
	ResourceLoaderHelper::get_singleton()->load_threaded_request("res://level/level0.tscn", [](Ref<Resource>) {
		// UtilityFunctions::print("Level1 loaded!!!!!!!!!");
	});
}

void World::_process(double delta) {
	ResourceLoaderHelper::get_singleton()->flush_queries();
}

void World::_exit_tree() {
	if (resource_loader_helper) {
		memdelete(resource_loader_helper);
	}
}
