#ifndef MATH_UTILS_H
#define MATH_UTILS_H

#include <cstdint>
#include <godot_cpp/core/defs.hpp>
#include <godot_cpp/core/error_macros.hpp>
#include <godot_cpp/core/math.hpp>
#include <godot_cpp/variant/utility_functions.hpp>
#include <godot_cpp/variant/vector2.hpp>
using namespace godot;

#include "utils/types.h"

//! Math工具
class MathUtils {
public:
	// ------------------------------------------
	//! 向上跳跃-计算速度y
	/*!
	 * \param p_jump_height 跳跃高度
	 * \param p_jump_duration 跳跃时间
	 */
	_FORCE_INLINE_ static real_t calculate_jump_speed_y(real_t p_jump_height, real_t p_jump_duration) {
		p_jump_duration = p_jump_duration == 0.0 ? (real_t)0.01 : p_jump_duration;
		return ((real_t)2.0 * (-p_jump_height)) / p_jump_duration;
	}

	//! 向上跳跃-计算重力
	/*!
	 * \param p_jump_height 跳跃高度
	 * \param p_jump_duration 跳跃时间
	 */
	_FORCE_INLINE_ static real_t calculate_jump_gravity(real_t p_jump_height, real_t p_jump_duration) {
		p_jump_duration = p_jump_duration == 0.0 ? (real_t)0.01 : p_jump_duration;
		return (real_t)-2.0 * (-p_jump_height) / (p_jump_duration * p_jump_duration);
	}

	//! 下坠-计算重力
	/*!
	 * \param p_jump_height 向上跳跃高度
	 * \param p_jump_duration 向上跳跃时间
	 * \param p_fall_gravity_multiplier 下坠重力相对于向上重力缩放
	 * \sa calculate_jump_gravity() * p_fall_gravity_multiplier
	 */
	_FORCE_INLINE_ static real_t calculate_fall_gravity(real_t p_jump_height, real_t p_jump_duration, real_t p_fall_gravity_multiplier) {
		return calculate_jump_gravity(p_jump_height, p_jump_duration) * p_fall_gravity_multiplier;
	}

	// ------------------------------------------
	//! 获取方向-枚举
	/*!
	 * \param p_vector 目标位置相对于自己的坐标
	 */
	_FORCE_INLINE_ static Direction get_direction(const Vector2& p_vector) {
		if (p_vector.length() == 0.0) {
			return Direction::None;
		}

		constexpr real_t PI1_8 = Math_PI * 1.0 / 8.0;
		constexpr real_t PI3_8 = Math_PI * 3.0 / 8.0;
		constexpr real_t PI5_8 = Math_PI * 5.0 / 8.0;
		constexpr real_t PI7_8 = Math_PI * 7.0 / 8.0;

		real_t radian = p_vector.angle();
		if (radian > -PI1_8 && radian <= PI1_8) {
			return Direction::Right;
		} else if (radian <= -PI7_8 || radian > PI7_8) {
			return Direction::Left;
		} else if (radian > -PI5_8 && radian <= -PI3_8) {
			return Direction::Up;
		} else if (radian <= PI5_8 && radian > PI3_8) {
			return Direction::Down;
		} else if (radian > -PI3_8 && radian <= -PI1_8) {
			return Direction::RightUp;
		} else if (radian <= PI3_8 && radian > PI1_8) {
			return Direction::RightDown;
		} else if (radian > -PI7_8 && radian <= -PI5_8) {
			return Direction::LeftUp;
		} else if (radian <= PI7_8 && radian > PI5_8) {
			return Direction::LeftDown;
		}
		ERR_FAIL_V_EDMSG(Direction::None, "Calcu direction error through vector2");
	}

	//! 获取方向-正负
	/*!
	 * \param p_vector 目标位置相对于自己的坐标
	 * \param[out] out_sign_x x轴
	 * \param[out] out_sign_y y轴
	 */
	_FORCE_INLINE_ static void get_direction_sign(const Vector2& p_vector, int8_t& out_sign_x, int8_t& out_sign_y) {
		get_direction_sign(get_direction(p_vector), out_sign_x, out_sign_y);
	}

	//! 获取方向-正负
	/*!
	 * \param p_dir 方向枚举
	 * \param[out] out_sign_x x轴
	 * \param[out] out_sign_y y轴
	 */
	_FORCE_INLINE_ static void get_direction_sign(Direction p_dir, int8_t& out_sign_x, int8_t& out_sign_y) {
		switch (p_dir) {
			case Direction::None:
				out_sign_x = 0;
				out_sign_y = 0;
				break;
			case Direction::Right:
				out_sign_x = 1;
				out_sign_y = 0;
				break;
			case Direction::Left:
				out_sign_x = -1;
				out_sign_y = 0;
				break;
			case Direction::Up:
				out_sign_x = 0;
				out_sign_y = -1;
				break;
			case Direction::Down:
				out_sign_x = 0;
				out_sign_y = 1;
				break;
			case Direction::RightUp:
				out_sign_x = 1;
				out_sign_y = -1;
				break;
			case Direction::RightDown:
				out_sign_x = 1;
				out_sign_y = 1;
				break;
			case Direction::LeftUp:
				out_sign_x = -1;
				out_sign_y = -1;
				break;
			case Direction::LeftDown:
				out_sign_x = -1;
				out_sign_y = 1;
				break;
		}
	}

	// ------------------------------------------
	//! 圆内随机找一点
	/*!
	 * \param p_position 圆心坐标
	 * \param p_radius 半径
	 */
	_FORCE_INLINE_ static Vector2 random_point_in_circle(const Vector2& p_position, float p_radius) {
		float radian = UtilityFunctions::randf_range(0.0, 2.0 * Math_PI);
		float radius = UtilityFunctions::randf_range(0.0, p_radius);
		return Vector2(p_position.x + radius * Math::cos(radian), p_position.y - radius * Math::sin(radian));
	}
};

#endif // MATH_UTILS_H
