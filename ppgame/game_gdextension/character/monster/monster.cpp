#include "monster.h"

#include <godot_cpp/classes/engine.hpp>
#include <godot_cpp/classes/global_constants.hpp>
#include <godot_cpp/classes/navigation_agent2d.hpp>
#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/core/defs.hpp>
#include <godot_cpp/core/object.hpp>
#include <godot_cpp/core/property_info.hpp>
#include <godot_cpp/variant/packed_string_array.hpp>
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
				if (nav_agent) {
					nav_agent->set_target_position(player->get_global_position());
					const Vector2& direction = nav_agent->get_next_path_position() - get_global_position();
					set_velocity(direction.normalized() * 50);
					move_and_slide();
				}
			}
		}
	}
}

// ----------------------------------------------------------------------------

void Monster::set_nav_agent(NavigationAgent2D* p_nav_agent) {
	nav_agent = p_nav_agent;
}

NavigationAgent2D* Monster::get_nav_agent() {
	return nav_agent;
}

void Monster::_bind_methods() {
	// nav_agent
	ClassDB::bind_method(D_METHOD(_STR(set_nav_agent), _STR(nav_agent)), &self_type::set_nav_agent);
	ClassDB::bind_method(D_METHOD(_STR(get_nav_agent)), &self_type::get_nav_agent);
	ADD_PROPERTY(PropertyInfo(Variant::Type::OBJECT, _STR(nav_agent), PropertyHint::PROPERTY_HINT_NODE_TYPE, NavigationAgent2D::get_class_static()), _STR(set_nav_agent), _STR(get_nav_agent));
}

PackedStringArray Monster::_get_configuration_warnings() const {
	PackedStringArray warnings = parent_type::_get_configuration_warnings();

	if (!nav_agent) {
		warnings.push_back("Not Set NavigationAgent2D");
	}

	return warnings;
}
