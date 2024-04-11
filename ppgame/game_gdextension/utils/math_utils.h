#ifndef MATH_UTILS_H
#define MATH_UTILS_H

#include <cstdint>
#include <godot_cpp/core/defs.hpp>
#include <godot_cpp/core/math.hpp>
#include <godot_cpp/variant/vector2.hpp>
using namespace godot;

namespace Utils {

inline Vector2 ground_move(double delta, int8_t input_sign_x, Vector2 curr_velocity, real_t max_speed_x, real_t acceleration_x, real_t deceleration_x, real_t turn_speed_x) {
	real_t walk_speed_change = 0.0;
	if (input_sign_x != 0) {
		if (Math::sign(input_sign_x) != Math::sign(curr_velocity.x)) {
			walk_speed_change = turn_speed_x * delta;
		} else {
			walk_speed_change = acceleration_x * delta;
		}
	} else {
		walk_speed_change = deceleration_x * delta;
	}

	real_t new_velocity_x = Math::move_toward(curr_velocity.x, input_sign_x * max_speed_x, walk_speed_change);
	return { new_velocity_x, curr_velocity.y };
}

inline real_t calculate_jump_speed_y(real_t jump_height, real_t jump_duration) {
	return (2.0 * (-jump_height)) / jump_duration;
}

inline real_t calculate_jump_gravity(real_t jump_height, real_t jump_duration) {
	return -(2.0 * (-jump_height)) / (jump_duration * jump_duration + 0.01);
}

inline real_t calculate_fall_gravity(real_t jump_height, real_t jump_duration, real_t fall_gravity_multiplier) {
	return calculate_jump_gravity(jump_height, jump_duration) * fall_gravity_multiplier;
}

inline Vector2 air_move(double delta, int8_t input_sign_x, Vector2 curr_velocity, real_t gravity) {
	Vector2 new_velocity;

	new_velocity.x = curr_velocity.x;
	new_velocity.y = curr_velocity.y + gravity * delta;

	return new_velocity;
}

} //namespace Utils

#endif // MATH_UTILS_H
