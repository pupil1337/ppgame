# class_name NavigationManager
# autoload
extends Node

var nav_mesh: NavigationPolygon
var nav_mesh_source_geometry_data: NavigationMeshSourceGeometryData2D
var nav_map_data: Dictionary # { agent_radius : { map_rid: RID, region_rid: RID, ref_counted: int }, ... }

## 导航地图数据
class NavMapData extends Object:
	var map_rid: RID
	var region_rid: RID
	var nav_mesh: NavigationPolygon
	var ref_counted: int = 0
	
	func _notification(what: int) -> void:
		if what == NOTIFICATION_PREDELETE:
			NavigationServer2D.free_rid(map_rid)
			NavigationServer2D.free_rid(region_rid)
			nav_mesh.free()


func _init() -> void:
	nav_mesh = NavigationPolygon.new()
	nav_mesh.parsed_collision_mask = Types.PhysicsLayer.WORLD | Types.PhysicsLayer.ONEWAY
	nav_mesh.source_geometry_mode = NavigationPolygon.SOURCE_GEOMETRY_GROUPS_EXPLICIT

## 解析关卡几何数据[br]
func parse_source_geometry(p_level: Level) -> void:
	nav_mesh.clear()
	nav_mesh_source_geometry_data.clear()
	
	NavigationServer2D.parse_source_geometry_data(nav_mesh, nav_mesh_source_geometry_data, p_level)

## 为不同大小的怪物创建导航地图[br]
func create_navigation_map_for_monster(p_monster: Monster) -> void:
	var agent_radius: int = _calculate_monster_nav_agent_radius(p_monster)
	var _data: NavMapData
	if not nav_map_data.has(agent_radius):
		_data = NavMapData.new()
		nav_map_data[agent_radius] = _data
		
		_data.map_rid = NavigationServer2D.map_create()
		NavigationServer2D.map_set_active(_data.map_rid, true)
		NavigationServer2D.map_set_cell_size(_data.map_rid, 1.0)
		
		_data.region_rid = NavigationServer2D.region_create()
		NavigationServer2D.region_set_enabled(_data.region_rid, true)
		NavigationServer2D.region_set_map(_data.region_rid, _data.map_rid)
		
		_data.nav_mesh = nav_mesh.duplicate(true)
		_data.nav_mesh.agent_radius = agent_radius
		
		NavigationServer2D.bake_from_source_geometry_data.call_deferred(_data.nav_mesh, nav_mesh_source_geometry_data)
		NavigationServer2D.region_set_navigation_polygon.call_deferred(_data.region_rid, _data.nav_mesh)
	else:
		_data = nav_map_data[agent_radius]
	
	p_monster.nav_agent.set_navigation_map(_data.map_rid)
	_data.ref_counted += 1

func destroy_navigation_map_by_monster(p_monster: Monster) -> void:
	var agent_radius: int = _calculate_monster_nav_agent_radius(p_monster)
	var _data: NavMapData = nav_map_data[agent_radius]
	_data.ref_counted -= 1
	if _data.ref_counted <= 0:
		_data.free()
		@warning_ignore("return_value_discarded")
		nav_map_data.erase(agent_radius)


## 计算怪物的导航代理半径
func _calculate_monster_nav_agent_radius(p_monster: Monster) -> int:
	var shape_size: Vector2 = (p_monster.collision_shape.shape as RectangleShape2D).size
	return ceili(maxf(shape_size.x, shape_size.y) / 2.0) + 2
