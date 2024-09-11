#include "monster_patrol_state.h"

#include <cstdint>
#include <godot_cpp/classes/character_body2d.hpp>
#include <godot_cpp/classes/rectangle_shape2d.hpp>
#include <godot_cpp/classes/ref.hpp>
#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/core/defs.hpp>
#include <godot_cpp/core/object.hpp>
#include <godot_cpp/core/property_info.hpp>
#include <godot_cpp/variant/array.hpp>
#include <godot_cpp/variant/color.hpp>
#include <godot_cpp/variant/string_name.hpp>
#include <godot_cpp/variant/typed_array.hpp>
#include <godot_cpp/variant/utility_functions.hpp>
#include <godot_cpp/variant/vector2.hpp>

#include "character/character_movement_component.h"
#include "character/monster/monster.h"
#include "character/monster/state/monster_state_condition.h"
#include "character/player/player.h"
#include "monster_behavior_none_state.h"
#include "utils/debug_draw_utils.h"
#include "utils/math_utils.h"
#include "utils/physics_utils.h"
#include "utils/types.h"
#include "world/world.h"

MonsterPatrolState::MonsterPatrolState() {
	is_default_state = true;
}

void MonsterPatrolState::enter() {
	patrol_direction_grounded = UtilityFunctions::randi_range(0, 1) == 0 ? Direction::Left : Direction::Right;
	if (monster && monster->get_motion_mode() == CharacterBody2D::MOTION_MODE_FLOATING && nav_agent && condition) {
		patrol_position_floating = MathUtils::random_point_in_circle(condition->global_position, patrol_radius_floating);
		nav_agent->set_target_position(patrol_position_floating);
	}
}

bool MonsterPatrolState::_check_player_in_view() {
	// 检测玩家仇恨
	if (World* world = World::get_singleton()) {
		if (Player* player = world->get_player()) {
			const Vector2& vfrom = monster->get_global_position();
			const Vector2& vmonster2player = player->get_global_position() - vfrom;
			if (!vmonster2player.is_zero_approx()) {
				const Vector2& vto = vfrom + vmonster2player.normalized() * view_length;
				RayResult res;
				if (PhysicsUtils::ray_cast(
							monster,
							res,
							vfrom,
							vto,
							(uint32_t)CollisionLayer::World | (uint32_t)CollisionLayer::Player,
							Array::make(monster),
							true,
							false,
							true)) {
					if (res.collider->get_class() == Player::get_class_static()) {
						// 角色
						DebugDrawUtils::draw_debug_line(vfrom, res.position, Color(1.0, 0.0, 0.0), 0.0001);
						DebugDrawUtils::draw_debug_line(res.position, vto, Color(1.0, 1.0, 1.0, 0.2), 0.0001);
						return true;
					} else {
						// 被非角色遮挡
						DebugDrawUtils::draw_debug_line(vfrom, res.position, Color(1.0, 1.0, 0.0), 0.0001);
						DebugDrawUtils::draw_debug_line(res.position, vto, Color(1.0, 1.0, 1.0, 0.2), 0.0001);
					}
				} else {
					// 无碰撞
					DebugDrawUtils::draw_debug_line(vfrom, vto, Color(0.0, 1.0, 0.0), 0.0001);
				}
			} else {
				// 中心点重合(几率很小)
				DebugDrawUtils::draw_debug_circle(vfrom, 3.0, Color(0.0, 0.0, 1.0), 2.0);
				return true;
			}
		}
	}

	return false;
}

void MonsterPatrolState::_update_patrol_target_grounded() {
	// 检测地形巡逻
	Ref<RectangleShape2D> shape = monster->shape_owner_get_shape(0, 0);
	if (shape.is_valid()) {
		const Vector2& shape_size = shape->get_size();
		Vector2 vfrom = monster->get_global_position();
		vfrom.y -= shape_size.y / 2.0 + 5.0;
		vfrom.x += patrol_direction_grounded == Direction::Right ? shape_size.x : -shape_size.x;
		const Vector2& vto = vfrom + Vector2(0.0, shape_size.y * 2.0);

		bool change_patrol_direction = false;
		RayResult res;
		if (PhysicsUtils::ray_cast(
					monster,
					res,
					vfrom,
					vto,
					(uint32_t)CollisionLayer::World,
					Array::make(monster),
					true,
					false,
					true)) {
			// 有碰撞
			if (res.position.y < monster->get_global_position().y + shape_size.y / 2.0) {
				// 高于脚 则掉头
				change_patrol_direction = true;
				DebugDrawUtils::draw_debug_circle(res.position, 3.0, Color(1.0, 0.0, 0.0), 2.0);
				DebugDrawUtils::draw_debug_line(res.position, vto, Color(1.0, 1.0, 1.0, 0.2), 2.0);
			} else {
				// 不高于脚
				DebugDrawUtils::draw_debug_line(vfrom, res.position, Color(0.0, 1.0, 0.0), 0.001);
				DebugDrawUtils::draw_debug_line(res.position, vto, Color(1.0, 1.0, 1.0, 0.2), 0.001);
			}
		} else {
			// 无碰撞 说明无处可走 则掉头
			change_patrol_direction = true;
			DebugDrawUtils::draw_debug_line(vfrom, vto, Color(1.0, 0.0, 0.0), 2.0);
		}
		if (change_patrol_direction) {
			patrol_direction_grounded = patrol_direction_grounded == Direction::Right ? Direction::Left : Direction::Right;
		}
	}
}

void MonsterPatrolState::_update_patrol_target_floating() {
	if (nav_agent && condition) {
		if (nav_agent->is_navigation_finished()) {
			patrol_position_floating = MathUtils::random_point_in_circle(condition->global_position, patrol_radius_floating);
			nav_agent->set_target_position(patrol_position_floating);
		}
	}
}

StringName MonsterPatrolState::on_process(double delta) {
	(void)delta;
	if (monster) {
		// 检测玩家仇恨
		if (_check_player_in_view()) {
			// TODO
			return MonsterBehaviorNoneState::get_class_static();
		}

		switch (monster->get_motion_mode()) {
			case CharacterBody2D::MOTION_MODE_GROUNDED: {
				_update_patrol_target_grounded();
				break;
			}
			case CharacterBody2D::MOTION_MODE_FLOATING: {
				_update_patrol_target_floating();
				break;
			}
		}
	}

	return StringName();
}

void MonsterPatrolState::on_physics_process(double delta) {
	if (monster && character_movement_component && condition) {
		switch (monster->get_motion_mode()) {
			case CharacterBody2D::MOTION_MODE_GROUNDED: {
				character_movement_component->input_move(
						delta,
						condition->velocity,
						patrol_direction_grounded == Direction::Right ? 1 : -1,
						character_movement_component->get_walk_acceleration(),
						character_movement_component->get_walk_deceleration(),
						character_movement_component->get_walk_turn_speed(),
						character_movement_component->get_walk_max_speed(),
						0.0);
				break;
			}
			case CharacterBody2D::MOTION_MODE_FLOATING: {
				// TODO
				if (nav_agent && !nav_agent->is_navigation_finished()) {
					const Vector2& dir = (nav_agent->get_next_path_position() - condition->global_position).normalized();
					monster->set_velocity(dir * character_movement_component->get_walk_max_speed());
					monster->move_and_slide();
				}
				break;
			}
		}
	}
}

void MonsterPatrolState::exit() {
}

// ----------------------------------------------------------------------------

void MonsterPatrolState::set_view_length(int p_view_length) {
	view_length = p_view_length;
}

int MonsterPatrolState::get_view_length() {
	return view_length;
}

void MonsterPatrolState::set_patrol_radius_floating(int p_patrol_radius_floating) {
	patrol_radius_floating = p_patrol_radius_floating;
}

int MonsterPatrolState::get_patrol_radius_floating() {
	return patrol_radius_floating;
}

void MonsterPatrolState::_bind_methods() {
	// view_length
	ClassDB::bind_method(D_METHOD(_STR(set_view_length), _STR(view_length)), &self_type::set_view_length);
	ClassDB::bind_method(D_METHOD(_STR(get_view_length)), &self_type::get_view_length);
	ADD_PROPERTY(PropertyInfo(Variant::Type::INT, _STR(view_length)), _STR(set_view_length), _STR(get_view_length));

	ADD_GROUP("floating", "");
	{
		// patrol_radius_floating
		ClassDB::bind_method(D_METHOD(_STR(set_patrol_radius_floating), _STR(patrol_radius_floating)), &self_type::set_patrol_radius_floating);
		ClassDB::bind_method(D_METHOD(_STR(get_patrol_radius_floating)), &self_type::get_patrol_radius_floating);
		ADD_PROPERTY(PropertyInfo(Variant::Type::INT, _STR(patrol_radius_floating)), _STR(set_patrol_radius_floating), _STR(get_patrol_radius_floating));
	}
}
