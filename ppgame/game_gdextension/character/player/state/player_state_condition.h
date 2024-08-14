#ifndef PLAYER_STATE_CONDITION_H
#define PLAYER_STATE_CONDITION_H

#include <cstdint>
#include <godot_cpp/variant/vector2.hpp>
using namespace godot;

//! 角色状态条件
struct PlayerStateCondition {
	PlayerStateCondition() {}

	// ------------------------------------------
	// logic
	// ------------------------------------------
	// input
	int8_t input_sign_x = 0; //!< x轴输入方向
	int8_t input_sign_y = 0; //!< y轴输入方向
	bool just_pressed_jump = false; //!< 刚刚输入jump
	bool just_pressed_attack = false; //!< 刚刚输入attack

	// ------------------------------------------
	// physics
	// ------------------------------------------
	// state
	bool on_ground = false; //!< 是否在地面上
	bool can_jump = false; //!< 是否可以跳跃
	Vector2 velocity; //!< 角色速度
};

#endif // PLAYER_STATE_CONDITION_H
