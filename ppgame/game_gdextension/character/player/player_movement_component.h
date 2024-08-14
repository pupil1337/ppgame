#ifndef PLAYER_MOVEMENT_COMPONENT_H
#define PLAYER_MOVEMENT_COMPONENT_H

#include <cstdint>
#include <godot_cpp/classes/sprite2d.hpp>
#include <godot_cpp/classes/wrapped.hpp>
#include <godot_cpp/core/defs.hpp>
#include <godot_cpp/variant/vector2.hpp>
using namespace godot;

#include "framework/component.h"

class Player;

//! 角色移动组件
class PlayerMovementComponent : public Component {
	GDCLASS(PlayerMovementComponent, Component)

public:
	//! 移动输入
	/*!
	 * \param p_delta DeltaTime
	 * \param p_curr_velocity 当前角色速度
	 * \param p_input_sign_x x轴输入方向正负
	 * \param p_acceleration_x x轴输入加速度
	 * \param p_deceleration_x x轴不输入时减速度
	 * \param p_turn_speed_x x轴转向速度
	 * \param p_max_speed_x x轴最大速度
	 * \param p_gravity y轴重力
	 */
	void input_move(double p_delta, const Vector2& p_curr_velocity, int8_t p_input_sign_x, real_t p_acceleration_x, real_t p_deceleration_x, real_t p_turn_speed_x, real_t p_max_speed_x, real_t p_gravity);

	//! 向上跳跃
	/*!
	 * \param p_curr_velocity 当前角色速度
	 * \param p_jump_height 向上跳跃高度
	 * \param p_jump_duration 向上跳跃持续时间
	 */
	void jump(const Vector2& p_curr_velocity, real_t p_jump_height, real_t p_jump_duration);

	//! 向下跳跃(单向平台)
	bool down_jump();

	real_t get_walk_acceleration();
	real_t get_walk_deceleration();
	real_t get_walk_turn_speed();
	real_t get_walk_max_speed();
	real_t get_jump_height();
	real_t get_jump_duration();
	real_t get_fall_gravity_multiplayer();

private:
	void _move_and_slide();

public:
	PlayerMovementComponent() {}

private:
	Player* player = nullptr; //!< 角色
	Sprite2D* player_sprite = nullptr; //!< 角色-精灵
	bool sprite_face_to_input = true; //!< 精灵朝向输入方向

	//! 步行参数
	struct WalkSetting {
		real_t acceleration = 600.0; //!< 加速度
		real_t deceleration = 5000.0; //!< 减速度
		real_t turn_speed = 1200.0; //!< 转向速度
		real_t max_speed = 400.0; //!< 最大速度
	} walk_setting;

	//! 跳跃参数
	struct JumpSetting {
		real_t height = 96.0; //!< 高度
		real_t duration = 0.4; //!< 持续时间
	} jump_setting;

	//! 下坠参数
	struct FallSetting {
		real_t gravity_multiplayer = 2.0; //!< 与跳跃相比重力系数
	} fall_setting;

	// ------------------------------------------

private:
	void set_walk_acceleration(real_t p_acceleration);
	void set_walk_deceleration(real_t p_deceleration);
	void set_walk_turn_speed(real_t p_turn_speed);
	void set_walk_max_speed(real_t p_max_speed);
	void set_jump_height(real_t p_height);
	void set_jump_duration(real_t p_duration);
	void set_fall_gravity_multiplayer(real_t p_multiplayer);

public:
	virtual void _ready() override;

protected:
	static void _bind_methods();
};

#endif // PLAYER_MOVEMENT_COMPONENT_H
