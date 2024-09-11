#ifndef SKYNET_H
#define SKYNET_H

#include <cstdint>
#include <godot_cpp/classes/navigation_mesh_source_geometry_data2d.hpp>
#include <godot_cpp/classes/navigation_polygon.hpp>
#include <godot_cpp/classes/navigation_region2d.hpp>
#include <godot_cpp/classes/object.hpp>
#include <godot_cpp/classes/ref.hpp>
#include <godot_cpp/classes/wrapped.hpp>
#include <godot_cpp/templates/hash_map.hpp>
#include <godot_cpp/variant/rid.hpp>
using namespace godot;

class Monster;
class World;
class Level;

//! 怪物管理系统
class Skynet : public Object {
	GDCLASS(Skynet, Object)

	static Skynet* singleton;

public:
	//! 解析关卡几何数据
	void parse_source_geometry(Level* p_level);
	//! 为不同大小的怪物创建导航地图
	void create_navigation_map_for_monster(Monster* p_monster);
	//! 销毁此怪物创建的导航地图
	void destroy_this_monster_navigation_map(Monster* p_monster);

private:
	uint32_t _get_monster_nav_agent_radius(Monster* p_monster);

public:
	static Skynet* get_singleton();
	Skynet();
	~Skynet();

private:
	Ref<NavigationPolygon> nav_mesh_for_source_geometry;
	Ref<NavigationMeshSourceGeometryData2D> nav_source_geometry;

	World* world = nullptr;

	struct NavMapData {
		RID map_rid;
		RID region_rid;
		Ref<NavigationPolygon> nav_mesh;
		uint64_t nav_region_id; // NavigationRegion2D
		uint32_t ref_counted = 0;
	};

	HashMap<uint32_t, NavMapData> nav_maps; //! 代理半径->导航地图数据

	// ------------------------------------------

protected:
	static void _bind_methods() {}
};

#endif // SKYNET_H
