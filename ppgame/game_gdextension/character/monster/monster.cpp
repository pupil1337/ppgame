#include "monster.h"

#include <godot_cpp/classes/collision_shape2d.hpp>
#include <godot_cpp/classes/engine.hpp>
#include <godot_cpp/classes/navigation_agent2d.hpp>
#include <godot_cpp/variant/callable_method_pointer.hpp>

#include "world/skynet.h"

void Monster::_ready() {
	parent_type::_ready();

	if (!Engine::get_singleton()->is_editor_hint()) {
		callable_mp(Skynet::get_singleton(), &Skynet::create_navigation_map_for_monster).call_deferred(this);
	}
}

void Monster::_exit_tree() {
	parent_type::_exit_tree();

	if (!Engine::get_singleton()->is_editor_hint()) {
		Skynet::get_singleton()->destroy_this_monster_navigation_map(this);
	}
}

void Monster::_process(double p_delta) {
	parent_type::_process(p_delta);
}

void Monster::_physics_process(double p_delta) {
	parent_type::_physics_process(p_delta);
}

NavigationAgent2D* Monster::get_nav_agent() {
	return get_node<NavigationAgent2D>("NavigationAgent2D");
}

CollisionShape2D* Monster::get_collision_shape() {
	return get_node<CollisionShape2D>("CollisionShape2D");
}
