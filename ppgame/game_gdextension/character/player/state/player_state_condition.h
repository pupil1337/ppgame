#ifndef PLAYER_STATE_CONDITION_H
#define PLAYER_STATE_CONDITION_H

#include <cstdint>
#include <godot_cpp/variant/vector2.hpp>
using namespace godot;

struct PlayerStateCondition {
	// ------------------------------------------
	// logic
	// ------------------------------------------
	// input
	int8_t input_sign_x = 0;
	bool just_pressed_jump = false;

	// ------------------------------------------
	// physics
	// ------------------------------------------
	// state
	bool on_ground = false;
	bool can_jump = false;
	Vector2 velocity;
};

#endif // PLAYER_STATE_CONDITION_H
