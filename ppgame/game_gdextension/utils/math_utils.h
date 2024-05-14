#ifndef MATH_UTILS_H
#define MATH_UTILS_H

#include <cstdint>
#include <godot_cpp/core/defs.hpp>
#include <godot_cpp/core/error_macros.hpp>
#include <godot_cpp/core/math.hpp>
#include <godot_cpp/variant/vector2.hpp>
using namespace godot;

enum Direction {
	Right,
	Left,
	Up,
	Down,
	RightUp,
	RightDown,
	LeftUp,
	LeftDown,
	None
};

class MathUtils {
public:
	// ------------------------------------------
	_FORCE_INLINE_ static real_t calculate_jump_speed_y(real_t jump_height, real_t jump_duration) {
		jump_duration = jump_duration == 0.0 ? (real_t)0.01 : jump_duration;
		return ((real_t)2.0 * (-jump_height)) / jump_duration;
	}

	_FORCE_INLINE_ static real_t calculate_jump_gravity(real_t jump_height, real_t jump_duration) {
		jump_duration = jump_duration == 0.0 ? (real_t)0.01 : jump_duration;
		return (real_t)-2.0 * (-jump_height) / (jump_duration * jump_duration);
	}

	_FORCE_INLINE_ static real_t calculate_fall_gravity(real_t jump_height, real_t jump_duration, real_t fall_gravity_multiplier) {
		return calculate_jump_gravity(jump_height, jump_duration) * fall_gravity_multiplier;
	}

	// ------------------------------------------
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

	_FORCE_INLINE_ static void get_direction_sign(const Vector2& p_vector, int8_t& in_sign_x, int8_t& in_sign_y) {
		get_direction_sign(get_direction(p_vector), in_sign_x, in_sign_y);
	}

	_FORCE_INLINE_ static void get_direction_sign(Direction p_dir, int8_t& in_sign_x, int8_t& in_sign_y) {
		switch (p_dir) {
			case Direction::None:
				in_sign_x = 0;
				in_sign_y = 0;
				break;
			case Direction::Right:
				in_sign_x = 1;
				in_sign_y = 0;
				break;
			case Direction::Left:
				in_sign_x = -1;
				in_sign_y = 0;
				break;
			case Direction::Up:
				in_sign_x = 0;
				in_sign_y = -1;
				break;
			case Direction::Down:
				in_sign_x = 0;
				in_sign_y = 1;
				break;
			case Direction::RightUp:
				in_sign_x = 1;
				in_sign_y = -1;
				break;
			case Direction::RightDown:
				in_sign_x = 1;
				in_sign_y = 1;
				break;
			case Direction::LeftUp:
				in_sign_x = -1;
				in_sign_y = -1;
				break;
			case Direction::LeftDown:
				in_sign_x = -1;
				in_sign_y = 1;
				break;
		}
	}
};

#endif // MATH_UTILS_H
