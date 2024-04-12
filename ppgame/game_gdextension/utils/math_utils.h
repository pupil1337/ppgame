#ifndef MATH_UTILS_H
#define MATH_UTILS_H

#include <cstdint>
#include <godot_cpp/core/defs.hpp>
#include <godot_cpp/core/math.hpp>
#include <godot_cpp/variant/vector2.hpp>
using namespace godot;

class MathUtils {
public:
	static _FORCE_INLINE_ Vector2 input_move(double delta, Vector2 curr_velocity, int8_t input_sign_x, real_t acceleration_x, real_t deceleration_x, real_t turn_speed_x, real_t gravity, real_t max_speed_x) {
		// x
		real_t speed_change_x = 0.0;
		if (input_sign_x != 0) {
			if (Math::sign(input_sign_x) != Math::sign(curr_velocity.x)) {
				speed_change_x = turn_speed_x * delta;
			} else {
				speed_change_x = acceleration_x * delta;
			}
		} else {
			speed_change_x = deceleration_x * delta;
		}
		real_t new_velocity_x = Math::move_toward(curr_velocity.x, input_sign_x * max_speed_x, speed_change_x);

		// y
		real_t new_velocity_y = curr_velocity.y + gravity * delta;

		return { new_velocity_x, new_velocity_y };
	}

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
