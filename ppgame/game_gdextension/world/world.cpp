#include "world.h"

#include <godot_cpp/classes/engine.hpp>
#include <godot_cpp/classes/object.hpp>
#include <godot_cpp/classes/packed_scene.hpp>
#include <godot_cpp/classes/ref.hpp>
#include <godot_cpp/classes/resource.hpp>
#include <godot_cpp/classes/resource_loader.hpp>
#include <godot_cpp/core/memory.hpp>
#include <godot_cpp/variant/callable_method_pointer.hpp>

#include "async_loader/async_loader.h"
#include "level/level.h"

static AsyncLoader* async_loader = nullptr;

void World::_enter_tree() {
	parent_type::_enter_tree();

	if (!Engine::get_singleton()->is_editor_hint()) {
		async_loader = memnew(AsyncLoader);
	}
}

void World::_ready() {
	parent_type::_ready();

	if (!Engine::get_singleton()->is_editor_hint()) {
		AsyncLoader::get_singleton()->instance("res://level/level_0.tscn", callable_mp(this, &self_type::_level_instanced_callback));
	}
}

void World::_level_instanced_callback(Node* p_node) {
	Level* level = Object::cast_to<Level>(p_node);
	add_child(level);
}

void World::_process(double delta) {
	parent_type::_process(delta);
}

void World::_exit_tree() {
	parent_type::_exit_tree();

	if (!Engine::get_singleton()->is_editor_hint()) {
		if (async_loader) {
			memdelete(async_loader);
		}
	}
}
