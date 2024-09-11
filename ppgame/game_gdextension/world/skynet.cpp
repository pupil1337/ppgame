#include "skynet.h"

#include <cstdint>
#include <godot_cpp/classes/collision_shape2d.hpp>
#include <godot_cpp/classes/navigation_agent2d.hpp>
#include <godot_cpp/classes/navigation_mesh_source_geometry_data2d.hpp>
#include <godot_cpp/classes/navigation_polygon.hpp>
#include <godot_cpp/classes/navigation_region2d.hpp>
#include <godot_cpp/classes/navigation_server2d.hpp>
#include <godot_cpp/classes/object.hpp>
#include <godot_cpp/classes/rectangle_shape2d.hpp>
#include <godot_cpp/classes/ref.hpp>
#include <godot_cpp/core/math.hpp>
#include <godot_cpp/core/memory.hpp>
#include <godot_cpp/core/object.hpp>
#include <godot_cpp/variant/array.hpp>
#include <godot_cpp/variant/callable_method_pointer.hpp>
#include <godot_cpp/variant/packed_vector2_array.hpp>
#include <godot_cpp/variant/rid.hpp>
#include <godot_cpp/variant/utility_functions.hpp>
#include <godot_cpp/variant/vector2.hpp>

#include "character/monster/monster.h"
#include "level/level.h"
#include "utils/types.h"
#include "world/world.h"

Skynet* Skynet::singleton = nullptr;

Skynet* Skynet::get_singleton() {
	return singleton;
}

Skynet::Skynet() {
	singleton = this;

	nav_mesh_for_source_geometry.instantiate();
	nav_mesh_for_source_geometry->set_parsed_collision_mask((uint32_t)CollisionLayer::World | (uint32_t)CollisionLayer::OneWay);
	nav_mesh_for_source_geometry->set_source_geometry_mode(NavigationPolygon::SourceGeometryMode::SOURCE_GEOMETRY_GROUPS_EXPLICIT);
	nav_source_geometry.instantiate();
}

Skynet::~Skynet() {
	singleton = nullptr;
}

void Skynet::parse_source_geometry(Level* p_level) {
	nav_source_geometry->clear();
	nav_mesh_for_source_geometry->clear();

	if (p_level) {
		NavigationServer2D::get_singleton()->parse_source_geometry_data(nav_mesh_for_source_geometry, nav_source_geometry, p_level);

		nav_mesh_for_source_geometry->add_outline(p_level->get_navigation_mesh_polygon());
	}
}

uint32_t Skynet::_get_monster_nav_agent_radius(Monster* p_monster) {
	if (p_monster) {
		if (CollisionShape2D* collision_shape = p_monster->get_collision_shape()) {
			Ref<RectangleShape2D> shape = collision_shape->get_shape();
			if (shape.is_valid()) {
				const Vector2& shape_size = shape->get_size();
				return Math::ceil(Math::max(shape_size.x, shape_size.y) / 2.0) + 2;
			}
		}
	}

	return 0;
}

void Skynet::create_navigation_map_for_monster(Monster* p_monster) {
	if (p_monster) {
		if (NavigationAgent2D* nav_agent = p_monster->get_nav_agent()) {
			uint32_t agent_radius = _get_monster_nav_agent_radius(p_monster);
			if (agent_radius != 0) {
				if (!nav_maps.has(agent_radius)) {
					NavMapData nav_data;

					nav_data.map_rid = NavigationServer2D::get_singleton()->map_create();
					NavigationServer2D::get_singleton()->map_set_active(nav_data.map_rid, true);
					NavigationServer2D::get_singleton()->map_set_cell_size(nav_data.map_rid, 1.0);

					nav_data.region_rid = NavigationServer2D::get_singleton()->region_create();
					NavigationServer2D::get_singleton()->region_set_enabled(nav_data.region_rid, true);
					NavigationServer2D::get_singleton()->region_set_map(nav_data.region_rid, nav_data.map_rid);

					nav_data.nav_mesh = nav_mesh_for_source_geometry->duplicate(true);
					nav_data.nav_mesh->set_agent_radius(agent_radius);

					callable_mp(NavigationServer2D::get_singleton(), &NavigationServer2D::bake_from_source_geometry_data).call_deferred(nav_data.nav_mesh, nav_source_geometry, Callable());
					callable_mp(NavigationServer2D::get_singleton(), &NavigationServer2D::region_set_navigation_polygon).call_deferred(nav_data.region_rid, nav_data.nav_mesh);

					// 增加这个节点用于显示debug
					NavigationRegion2D* nav_region = memnew(NavigationRegion2D);
					nav_region->set_navigation_map(nav_data.map_rid);
					nav_region->set_navigation_polygon(nav_data.nav_mesh);
					World::get_singleton()->add_child(nav_region); // TODO
					nav_data.nav_region_id = nav_region->get_instance_id();

					nav_maps.insert(agent_radius, nav_data);

					UtilityFunctions::print("NavigationServer2D::get_singleton()->get_maps():", NavigationServer2D::get_singleton()->get_maps());
				}
				nav_agent->set_navigation_map(nav_maps.get(agent_radius).map_rid);
				nav_maps.get(agent_radius).ref_counted++;
			}
		}
	}
}

void Skynet::destroy_this_monster_navigation_map(Monster* p_monster) {
	uint32_t agent_radius = _get_monster_nav_agent_radius(p_monster);
	if (nav_maps.has(agent_radius)) {
		NavMapData& nav_data = nav_maps.get(agent_radius);
		nav_data.ref_counted--;
		if (nav_data.ref_counted <= 0) {
			if (NavigationRegion2D* nav_region = Object::cast_to<NavigationRegion2D>(ObjectDB::get_instance(nav_data.nav_region_id))) {
				nav_region->queue_free();
			}
			nav_maps.erase(agent_radius);
			NavigationServer2D::get_singleton()->free_rid(nav_data.map_rid);
		}
	}
}
