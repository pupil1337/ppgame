class_name PhysicsUtils extends Object

## 射线检测[br]
## [param p_world_content]: 场景中的节点[br]
## [param p_from]: 起点[br]
## [param p_to]: 终点[br]
## [param out_result]: 检测结果[br]
## [param p_collision_mask]: 碰撞物理层掩码[br]
## [param p_exclude]: 排除的RID[br]
## [param p_collide_with_areas]: 是否检测Area[br]
## [param p_collide_with_bodies]: 是否检测Body[br]
## [param p_hit_from_inside]: 是否从内部开始检测[br]
static func ray_cast(p_world_content: CanvasItem, p_from: Vector2, p_to: Vector2, out_result: Types.RayResult, p_collision_mask: int = 0xffffffff, p_exclude: Array[RID] = [], p_collide_with_areas: bool = false, p_collide_with_bodies: bool = true, p_hit_from_inside: bool = false) -> bool:
	var query_param: PhysicsRayQueryParameters2D = PhysicsRayQueryParameters2D.create(p_from, p_to, p_collision_mask, p_exclude)
	query_param.collide_with_areas = p_collide_with_areas
	query_param.collide_with_bodies = p_collide_with_bodies
	query_param.hit_from_inside = p_hit_from_inside
	
	var res: Dictionary = p_world_content.get_world_2d().direct_space_state.intersect_ray(query_param)
	if res.is_empty():
		return false
	out_result.position = res["position"]
	out_result.normal = res["normal"]
	out_result.collider_id = res["collider_id"]
	out_result.collider = res["collider"]
	out_result.shape = res["shape"]
	out_result.rid = res["rid"]
	return true


## 形状检测-矩形[br]
## [param p_world_content]: 场景中的节点[br]
## [param p_transform]: 矩形中心Transform[br]
## [param p_half_extents]: 矩形半范围[br]
## [param p_motion]: 位移[br]
## [param out_results]: 检测结果[br]
## [param p_collision_mask]: 碰撞物理层掩码[br]
## [param p_exclude]: 排除的RID[br]
## [param p_collide_with_areas]: 是否检测Area[br]
## [param p_collide_with_bodies]: 是否检测Body[br]
## [param p_margin]: 形状的碰撞边距[br]
## [param p_max_results]: 最大相交数量[br]
static func shape_cast_rectangle(p_world_content: CanvasItem, p_transform: Transform2D, p_half_extents: Vector2, p_motion: Vector2, out_results: Array[Types.ShapeResult], p_collision_mask: int = 0xffffffff, p_exclude: Array[RID] = [], p_collide_with_areas: bool = false, p_collide_with_bodies: bool = true, p_margin: float = 0.0, p_max_results: int = 32) -> bool:
	var res: bool
	
	var shape_rid: RID = PhysicsServer2D.rectangle_shape_create()
	PhysicsServer2D.shape_set_data(shape_rid, p_half_extents)
	res = _shape_cast_internal(p_world_content, shape_rid, p_transform, p_motion, out_results, p_collision_mask, p_exclude, p_collide_with_areas, p_collide_with_bodies, p_margin, p_max_results)
	PhysicsServer2D.free_rid(shape_rid)
	
	return res


#region
static func _shape_cast_internal(p_world_content: CanvasItem, p_shape_rid: RID, p_transform: Transform2D, p_motion: Vector2, out_results: Array[Types.ShapeResult], p_collision_mask: int, p_exclude: Array[RID], p_collide_with_areas: bool, p_collide_with_bodies: bool, p_margin: float, p_max_results: int) -> bool:
	var query_param: PhysicsShapeQueryParameters2D = PhysicsShapeQueryParameters2D.new()
	query_param.shape_rid = p_shape_rid
	query_param.transform = p_transform
	query_param.motion = p_motion
	query_param.collision_mask = p_collision_mask
	query_param.exclude = p_exclude
	query_param.collide_with_areas = p_collide_with_areas
	query_param.collide_with_bodies = p_collide_with_bodies
	query_param.margin = p_margin
	
	var ress: Array[Dictionary] = p_world_content.get_world_2d().direct_space_state.intersect_shape(query_param, p_max_results)
	if ress.is_empty():
		return false
	for res: Dictionary in ress:
		var shape_result: Types.ShapeResult = Types.ShapeResult.new()
		shape_result.rid = res["rid"]
		shape_result.collider_id = res["collider_id"]
		shape_result.collider = res["collider"]
		shape_result.shape = res["shape"]
		out_results.push_back(shape_result)
	return true
#endregion
