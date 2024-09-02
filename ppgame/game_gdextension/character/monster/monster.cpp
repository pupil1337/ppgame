#include "monster.h"

#include <godot_cpp/classes/engine.hpp>
#include <godot_cpp/classes/navigation_agent2d.hpp>
#include <godot_cpp/variant/vector2.hpp>

#include "character/player/player.h"
#include "world/world.h"

void Monster::_process(double p_delta) {
	parent_type::_process(p_delta);
}

void Monster::_physics_process(double p_delta) {
	parent_type::_physics_process(p_delta);

	if (!Engine::get_singleton()->is_editor_hint()) {
		if (World* world = World::get_world(this)) {
			if (Player* player = world->get_player()) {
				if (NavigationAgent2D* nav_agent = get_nav_agent()) {
					nav_agent->set_target_position(player->get_global_position());
					const Vector2& direction = nav_agent->get_next_path_position() - get_global_position();
					set_velocity(direction.normalized() * 50);
					move_and_slide();
				}
			}
		}
	}
}

NavigationAgent2D* Monster::get_nav_agent() {
	return get_node<NavigationAgent2D>("NavigationAgent2D");
}
