#ifndef PLAYER_STATE_CONDITION_H
#define PLAYER_STATE_CONDITION_H

#include <godot_cpp/variant/vector2.hpp>
using namespace godot;

struct PlayerStateCondition {
	Vector2 input_motion;
	bool pressed_jump = false;
	bool on_ground = false;
};

#endif // PLAYER_STATE_CONDITION_H
