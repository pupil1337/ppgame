#ifndef MATH_UTILS_H
#define MATH_UTILS_H

#include <godot_cpp/core/defs.hpp>
#include <godot_cpp/core/math.hpp>
#include <godot_cpp/variant/vector2.hpp>
using namespace godot;

class MathUtils {
public:
	static _FORCE_INLINE_ real_t calculate_jump_speed_y(real_t jump_height, real_t jump_duration) {
		return (2.0 * (-jump_height)) / jump_duration;
	}

	static _FORCE_INLINE_ real_t calculate_jump_gravity(real_t jump_height, real_t jump_duration) {
		return -(2.0 * (-jump_height)) / (jump_duration * jump_duration + 0.01);
	}

	static _FORCE_INLINE_ real_t calculate_fall_gravity(real_t jump_height, real_t jump_duration, real_t fall_gravity_multiplier) {
		return calculate_jump_gravity(jump_height, jump_duration) * fall_gravity_multiplier;
	}
};

#endif // MATH_UTILS_H
