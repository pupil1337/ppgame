#ifndef PHYSICS_UTILS_H
#define PHYSICS_UTILS_H

#include <cstdint>
#include <godot_cpp/classes/node2d.hpp>
#include <godot_cpp/classes/physics_direct_space_state2d.hpp>
#include <godot_cpp/classes/physics_ray_query_parameters2d.hpp>
#include <godot_cpp/classes/physics_server2d.hpp>
#include <godot_cpp/classes/physics_shape_query_parameters2d.hpp>
#include <godot_cpp/classes/ref.hpp>
#include <godot_cpp/classes/world2d.hpp>
#include <godot_cpp/core/defs.hpp>
#include <godot_cpp/core/object_id.hpp>
#include <godot_cpp/templates/vector.hpp>
#include <godot_cpp/variant/dictionary.hpp>
#include <godot_cpp/variant/rid.hpp>
#include <godot_cpp/variant/transform2d.hpp>
#include <godot_cpp/variant/typed_array.hpp>
#include <godot_cpp/variant/vector2.hpp>
using namespace godot;

#include "utils/types.h"

//! Physics工具
class PhysicsUtils {
public:
	//! 射线检测
	/*!
	 * \param p_world_context_2d World Context
	 * \param out_result 检测结果
	 * \param p_from 要查询的射线起点, 使用全局坐标.
	 * \param p_to 要查询的射线终点，使用全局坐标.
	 * \param p_collision_mask 查询将检测的物理层(作为位掩码)
	 * \param p_excludes 排除的Rid
	 * \param p_collide_with_bodies 是否检测Body
	 * \param p_collide_with_areas 是否检测Area
	 * \param p_hit_from_inside 如果为true, 查询会在从形状内部开始时检测到命中. 在此情况下, 碰撞法线将为Vector2(0, 0). 不会影响凹多边形形状.
	 * \return 是否检测到相交
	 */
	_FORCE_INLINE_ static bool ray_cast(Node2D* p_world_context_2d, RayResult& out_result, const Vector2& p_from, const Vector2& p_to, uint32_t p_collision_mask, const TypedArray<RID>& p_excludes = {}, bool p_collide_with_bodies = true, bool p_collide_with_areas = false, bool p_hit_from_inside = false) {
		if (p_world_context_2d) {
			Ref<World2D> world_2d = p_world_context_2d->get_world_2d();
			if (world_2d.is_valid()) {
				if (PhysicsDirectSpaceState2D* dss = PhysicsServer2D::get_singleton()->space_get_direct_state(world_2d->get_space())) {
					Ref<PhysicsRayQueryParameters2D> ray_params = PhysicsRayQueryParameters2D::create(p_from, p_to, p_collision_mask, p_excludes);
					p_collide_with_bodies != true ? ray_params->set_collide_with_bodies(false) : (void)0;
					p_collide_with_areas != false ? ray_params->set_collide_with_areas(true) : (void)0;
					p_hit_from_inside != false ? ray_params->set_hit_from_inside(true) : (void)0;

					const Dictionary& ray_res = dss->intersect_ray(ray_params);
					if (!ray_res.is_empty()) {
						out_result.position = ray_res["position"];
						out_result.normal = ray_res["normal"];
						out_result.rid = ray_res["rid"];
						out_result.collider_id = ray_res["collider_id"].operator ObjectID();
						out_result.collider = ray_res["collider"];
						out_result.shape = ray_res["shape"];
						return true;
					}
				}
			}
		}

		return false;
	}

	//! 形状检测
	/*!
	 * \tparam shape_type 形状类型
	 * \param p_world_context_2d World Context
	 * \param out_results 检测结果
	 * \param p_shape_data 形状大小数据
	 * \param p_transform 被查询形状的变换矩阵
	 * \param p_motion 正在查询的形状的运动
	 * \param p_collision_masks 查询将检测的物理层(作为位掩码)
	 * \param p_max_results 限制最大相交数量
	 * \param p_excludes 将被排除在碰撞之外的对象的RID列表. 请使用CollisionObject2D.get_rid()来获取与派生自CollisionObject2D的节点关联的RID.
	 * \param p_collide_with_bodies 是否检测Body
	 * \param p_collide_with_areas 是否检测Area
	 * \param p_margin 形状的碰撞边距
	 * \return 是否检测到相交
	 */
	template <PhysicsServer2D::ShapeType shape_type, typename T>
	_FORCE_INLINE_ static bool shape_cast(Node2D* p_world_context_2d, Vector<ShapeResult>& out_results, const T& p_shape_data, const Transform2D& p_transform, const Vector2& p_motion, uint32_t p_collision_masks, int32_t p_max_results = 32, const TypedArray<RID>& p_excludes = {}, bool p_collide_with_bodies = true, bool p_collide_with_areas = false, double p_margin = 0.0);

	_FORCE_INLINE_ static bool _shape_cast_internal(Node2D* p_world_context_2d, Vector<ShapeResult>& out_results, const RID& p_shape_rid, const Transform2D& p_transform, const Vector2& p_motion, uint32_t p_collision_masks, int32_t p_max_results, const TypedArray<RID>& p_excludes, bool p_collide_with_bodies, bool p_collide_with_areas, double p_margin) {
		if (p_world_context_2d) {
			Ref<World2D> world_2d = p_world_context_2d->get_world_2d();
			if (world_2d.is_valid()) {
				if (PhysicsDirectSpaceState2D* dss = PhysicsServer2D::get_singleton()->space_get_direct_state(world_2d->get_space())) {
					Ref<PhysicsShapeQueryParameters2D> shape_params;
					shape_params.instantiate();
					shape_params->set_shape_rid(p_shape_rid);
					shape_params->set_transform(p_transform);
					shape_params->set_motion(p_motion);
					shape_params->set_exclude(p_excludes);
					shape_params->set_collision_mask(p_collision_masks);
					p_collide_with_bodies != true ? shape_params->set_collide_with_bodies(false) : (void)0;
					p_collide_with_areas != false ? shape_params->set_collide_with_areas(true) : (void)0;
					p_margin != 0.0 ? shape_params->set_margin(p_margin) : (void)0;

					TypedArray<Dictionary> shape_res = dss->intersect_shape(shape_params, p_max_results);
					if (!shape_res.is_empty()) {
						out_results.clear();
						for (int64_t i = 0; i < shape_res.size(); ++i) {
							ShapeResult tRes;
							tRes.rid = Dictionary(shape_res[i])["rid"];
							tRes.collider_id = Dictionary(shape_res[i])["collider_id"].operator ObjectID();
							tRes.collider = Dictionary(shape_res[i])["collider"];
							tRes.shape = Dictionary(shape_res[i])["shape"];
							out_results.push_back(tRes);
						}

						return true;
					}
				}
			}
		}

		return false;
	}
};

//! 矩形检测(特化)
/*!
 * \param p_shape_data Vector2类型的half_extents
 * \param p_transform 矩形中心矩阵
 */
template <>
_FORCE_INLINE_ bool PhysicsUtils::shape_cast<PhysicsServer2D::ShapeType::SHAPE_RECTANGLE, Vector2>(Node2D* p_world_context_2d, Vector<ShapeResult>& out_results, const Vector2& p_shape_data, const Transform2D& p_transform, const Vector2& p_motion, uint32_t p_collision_masks, int32_t p_max_results /* = 32 */, const TypedArray<RID>& p_excludes /* = {} */, bool p_collide_with_bodies /* = true */, bool p_collide_with_areas /* = false */, double p_margin /* = 0.0 */) {
	bool res;

	const RID& shape_rid = PhysicsServer2D::get_singleton()->rectangle_shape_create();
	PhysicsServer2D::get_singleton()->shape_set_data(shape_rid, p_shape_data);
	res = _shape_cast_internal(p_world_context_2d, out_results, shape_rid, p_transform, p_motion, p_collision_masks, p_max_results, p_excludes, p_collide_with_bodies, p_collide_with_areas, p_margin);
	PhysicsServer2D::get_singleton()->free_rid(shape_rid);

	return res;
}

#endif // PHYSICS_UTILS_H
