#ifndef PHYSICS_UTILS_H
#define PHYSICS_UTILS_H

#include <cstdint>
#include <godot_cpp/classes/node2d.hpp>
#include <godot_cpp/classes/physics_direct_space_state2d.hpp>
#include <godot_cpp/classes/physics_ray_query_parameters2d.hpp>
#include <godot_cpp/classes/physics_server2d.hpp>
#include <godot_cpp/classes/ref.hpp>
#include <godot_cpp/classes/world2d.hpp>
#include <godot_cpp/core/defs.hpp>
#include <godot_cpp/core/object_id.hpp>
#include <godot_cpp/templates/vector.hpp>
#include <godot_cpp/variant/dictionary.hpp>
#include <godot_cpp/variant/rid.hpp>
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
	 * \param p_from 起始位置
	 * \param p_to 终点位置
	 * \param out_result 检测结果
	 * \param p_collision_layers 碰撞层
	 * \param p_exclude 排除的Rid
	 * \param collide_with_bodies 是否检测Body
	 * \param collide_with_areas 是否检测Area
	 * \param hit_from_inside 是否从形状内部开始时检测到命中
	 * \return 是否检测到碰撞物
	 */
	_FORCE_INLINE_ static bool ray_cast(Node2D* p_world_context_2d, const Vector2& p_from, const Vector2& p_to, RayResult& out_result, const Vector<CollisionLayer>& p_collision_layers, const Vector<RID>& p_exclude = {}, bool collide_with_bodies = true, bool collide_with_areas = false, bool hit_from_inside = false) {
		if (p_world_context_2d) {
			Ref<World2D> world_2d = p_world_context_2d->get_world_2d();
			if (world_2d.is_valid()) {
				if (PhysicsDirectSpaceState2D* dss = PhysicsServer2D::get_singleton()->space_get_direct_state(world_2d->get_space())) {
					uint32_t collision_mask = 0;
					for (int i = 0; i < p_collision_layers.size(); ++i) {
						collision_mask |= (uint32_t)p_collision_layers[i];
					}
					collision_mask = collision_mask == 0 ? (uint32_t)CollisionLayer::ALL : collision_mask;

					TypedArray<RID> exclude = {};
					for (int i = 0; i < p_exclude.size(); ++i) {
						exclude.append(p_exclude[i]);
					}

					const Ref<PhysicsRayQueryParameters2D>& ray_params = PhysicsRayQueryParameters2D::create(p_from, p_to, collision_mask, exclude);
					collide_with_bodies == false ? ray_params->set_collide_with_bodies(false) : (void)0;
					collide_with_areas == true ? ray_params->set_collide_with_areas(true) : (void)0;
					hit_from_inside == true ? ray_params->set_hit_from_inside(true) : (void)0;

					const Dictionary& res = dss->intersect_ray(ray_params);
					if (!res.is_empty()) {
						out_result.position = res["position"];
						out_result.normal = res["normal"];
						out_result.rid = res["rid"];
						out_result.collider_id = res["collider_id"].operator ObjectID();
						out_result.collider = res["collider"];
						out_result.shape = res["shape"];
						return true;
					}
				}
			}
		}

		return false;
	}
};

#endif // PHYSICS_UTILS_H
