#include "player_movement_component.h"

#include <cstdint>
#include <godot_cpp/classes/engine.hpp>
#include <godot_cpp/classes/physics_server2d.hpp>
#include <godot_cpp/classes/rectangle_shape2d.hpp>
#include <godot_cpp/classes/ref.hpp>
#include <godot_cpp/classes/sprite2d.hpp>
#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/core/defs.hpp>
#include <godot_cpp/core/math.hpp>
#include <godot_cpp/core/object.hpp>
#include <godot_cpp/core/property_info.hpp>
#include <godot_cpp/templates/vector.hpp>
#include <godot_cpp/variant/array.hpp>
#include <godot_cpp/variant/color.hpp>
#include <godot_cpp/variant/rect2.hpp>
#include <godot_cpp/variant/transform2d.hpp>
#include <godot_cpp/variant/variant.hpp>
#include <godot_cpp/variant/vector2.hpp>

#include "character/player/player.h"
#include "utils/debug_draw_utils.h"
#include "utils/math_utils.h"
#include "utils/physics_utils.h"
#include "utils/types.h"

void PlayerMovementComponent::_ready() {
	parent_type::_ready();

	if (!Engine::get_singleton()->is_editor_hint()) {
		if (actor) {
			player = static_cast<Player*>(actor);
			player_sprite = player->get_sprite();
		}
	}
}

void PlayerMovementComponent::input_move(double p_delta, const Vector2& p_curr_velocity, int8_t p_input_sign_x, real_t p_acceleration_x, real_t p_deceleration_x, real_t p_turn_speed_x, real_t p_max_speed_x, real_t p_gravity) {
	// x
	real_t speed_change_x = 0.0;
	if (p_input_sign_x != 0) {
		if (Math::sign(p_input_sign_x) != Math::sign(p_curr_velocity.x)) {
			speed_change_x = p_turn_speed_x * p_delta;
		} else {
			speed_change_x = p_acceleration_x * p_delta;
		}
	} else {
		speed_change_x = p_deceleration_x * p_delta;
	}
	real_t new_velocity_x = Math::move_toward(p_curr_velocity.x, p_input_sign_x * p_max_speed_x, speed_change_x);

	// y
	real_t new_velocity_y = p_curr_velocity.y + p_gravity * p_delta;

	// sprite_face_to_input
	if (sprite_face_to_input && p_input_sign_x != 0) {
		if (player_sprite) {
			player_sprite->set_flip_h(p_input_sign_x < 0);
		}
	}

	// move
	if (player) {
		player->set_velocity({ new_velocity_x, new_velocity_y });
		_move_and_slide();
	}
}

void PlayerMovementComponent::jump(const Vector2& p_curr_velocity, real_t p_jump_height, real_t p_jump_duration) {
	if (player) {
		real_t new_velocity_y;
		new_velocity_y = MathUtils::calculate_jump_speed_y(p_jump_height, p_jump_duration);

		player->set_velocity({ p_curr_velocity.x, new_velocity_y });
		_move_and_slide();
	}
}

bool PlayerMovementComponent::down_jump() {
	if (player) {
		uint32_t player_collision_mask = player->get_collision_mask();
		double player_snap_length = player->get_floor_snap_length();
		if (player_collision_mask & (uint32_t)CollisionLayer::OneWay) {
			Ref<RectangleShape2D> shape = player->shape_owner_get_shape(0, 0);
			if (shape.is_valid()) {
				Vector<ShapeResult> shape_results;
				DebugDrawUtils::draw_debug_rectangle(Rect2(player->get_global_position() - shape->get_size() / 2.0 + Vector2(0.0, player_snap_length * 2), shape->get_size()), Color(1.0, 0.0, 0.0), 3.0);
				if (PhysicsUtils::shape_cast<PhysicsServer2D::ShapeType::SHAPE_RECTANGLE>(
							player,
							shape_results,
							shape->get_size() / 2.0,
							player->get_global_transform(),
							Vector2(0.0, player_snap_length * 2),
							player_collision_mask,
							32,
							Array::make(player->get_rid()),
							true,
							false,
							0.0)) {
					bool has_oneway = false;
					for (int i = 0; i < shape_results.size(); ++i) {
						uint32_t collided_layer = PhysicsServer2D::get_singleton()->body_get_collision_layer(shape_results[i].rid);
						if (collided_layer & ~(uint32_t)CollisionLayer::OneWay) {
							return false;
						}
						has_oneway = true;
					}
					if (has_oneway) {
						player->set_collision_mask(player_collision_mask & ~(uint32_t)CollisionLayer::OneWay);
						player->global_translate(Vector2(0.0, player_snap_length * 2));
						player->move_and_slide();
						player->set_collision_mask(player_collision_mask);
						return !player->is_on_floor();
					}
				}
			}
		}
	}

	return false;
}

void PlayerMovementComponent::_move_and_slide() {
	if (player) {
		player->move_and_slide();
	}
}

real_t PlayerMovementComponent::get_walk_acceleration() {
	return walk_setting.acceleration;
}

real_t PlayerMovementComponent::get_walk_deceleration() {
	return walk_setting.deceleration;
}

real_t PlayerMovementComponent::get_walk_turn_speed() {
	return walk_setting.turn_speed;
}

real_t PlayerMovementComponent::get_walk_max_speed() {
	return walk_setting.max_speed;
}

real_t PlayerMovementComponent::get_jump_height() {
	return jump_setting.height;
}

real_t PlayerMovementComponent::get_jump_duration() {
	return jump_setting.duration;
}

real_t PlayerMovementComponent::get_fall_gravity_multiplayer() {
	return fall_setting.gravity_multiplayer;
}

// ----------------------------------------------------------------------------

void PlayerMovementComponent::set_walk_acceleration(real_t p_acceleration) {
	walk_setting.acceleration = p_acceleration;
}

void PlayerMovementComponent::set_walk_deceleration(real_t p_deceleration) {
	walk_setting.deceleration = p_deceleration;
}

void PlayerMovementComponent::set_walk_turn_speed(real_t p_turn_speed) {
	walk_setting.turn_speed = p_turn_speed;
}

void PlayerMovementComponent::set_walk_max_speed(real_t p_max_speed) {
	walk_setting.max_speed = p_max_speed;
}

void PlayerMovementComponent::set_jump_height(real_t p_height) {
	jump_setting.height = p_height;
}

void PlayerMovementComponent::set_jump_duration(real_t p_duration) {
	jump_setting.duration = p_duration;
}

void PlayerMovementComponent::set_fall_gravity_multiplayer(real_t p_multiplayer) {
	fall_setting.gravity_multiplayer = p_multiplayer;
}

void PlayerMovementComponent::_bind_methods() {
	ADD_GROUP("walk", "");
	{
		// acceleration
		ClassDB::bind_method(D_METHOD(_STR(set_walk_acceleration), _STR(acceleration)), &self_type::set_walk_acceleration);
		ClassDB::bind_method(D_METHOD(_STR(get_walk_acceleration)), &self_type::get_walk_acceleration);
		ADD_PROPERTY(PropertyInfo(Variant::Type::INT, _STR(acceleration)), _STR(set_walk_acceleration), _STR(get_walk_acceleration));

		// deceleration
		ClassDB::bind_method(D_METHOD(_STR(set_walk_deceleration), _STR(deceleration)), &self_type::set_walk_deceleration);
		ClassDB::bind_method(D_METHOD(_STR(get_walk_deceleration)), &self_type::get_walk_deceleration);
		ADD_PROPERTY(PropertyInfo(Variant::Type::INT, _STR(deceleration)), _STR(set_walk_deceleration), _STR(get_walk_deceleration));

		// turn_speed
		ClassDB::bind_method(D_METHOD(_STR(set_walk_turn_speed), _STR(turn_speed)), &self_type::set_walk_turn_speed);
		ClassDB::bind_method(D_METHOD(_STR(get_walk_turn_speed)), &self_type::get_walk_turn_speed);
		ADD_PROPERTY(PropertyInfo(Variant::Type::INT, _STR(turn_speed)), _STR(set_walk_turn_speed), _STR(get_walk_turn_speed));

		// max_speed
		ClassDB::bind_method(D_METHOD(_STR(set_walk_max_speed), _STR(max_speed)), &self_type::set_walk_max_speed);
		ClassDB::bind_method(D_METHOD(_STR(get_walk_max_speed)), &self_type::get_walk_max_speed);
		ADD_PROPERTY(PropertyInfo(Variant::Type::INT, _STR(max_speed)), _STR(set_walk_max_speed), _STR(get_walk_max_speed));
	}

	ADD_GROUP("jump", "");
	{
		// height
		ClassDB::bind_method(D_METHOD(_STR(set_jump_height), _STR(height)), &self_type::set_jump_height);
		ClassDB::bind_method(D_METHOD(_STR(get_jump_height)), &self_type::get_jump_height);
		ADD_PROPERTY(PropertyInfo(Variant::Type::INT, _STR(height)), _STR(set_jump_height), _STR(get_jump_height));

		// duration
		ClassDB::bind_method(D_METHOD(_STR(set_jump_duration), _STR(duration)), &self_type::set_jump_duration);
		ClassDB::bind_method(D_METHOD(_STR(get_jump_duration)), &self_type::get_jump_duration);
		ADD_PROPERTY(PropertyInfo(Variant::Type::FLOAT, _STR(duration)), _STR(set_jump_duration), _STR(get_jump_duration));
	}

	ADD_GROUP("fall", "");
	{
		// gravity_multiplayer
		ClassDB::bind_method(D_METHOD(_STR(set_fall_gravity_multiplayer), _STR(multiplayer)), &self_type::set_fall_gravity_multiplayer);
		ClassDB::bind_method(D_METHOD(_STR(get_fall_gravity_multiplayer)), &self_type::get_fall_gravity_multiplayer);
		ADD_PROPERTY(PropertyInfo(Variant::Type::FLOAT, _STR(gravity_multiplayer)), _STR(set_fall_gravity_multiplayer), _STR(get_fall_gravity_multiplayer));
	}
}
