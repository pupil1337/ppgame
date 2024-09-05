#include "monster.h"

#include <godot_cpp/classes/navigation_agent2d.hpp>

void Monster::_process(double p_delta) {
	parent_type::_process(p_delta);
}

void Monster::_physics_process(double p_delta) {
	parent_type::_physics_process(p_delta);
}

NavigationAgent2D* Monster::get_nav_agent() {
	return get_node<NavigationAgent2D>("NavigationAgent2D");
}
