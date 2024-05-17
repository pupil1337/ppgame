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

class PlayerMovementComponent : public Component {
	GDCLASS(PlayerMovementComponent, Component)

public:
	void input_move(double delta, const Vector2& curr_velocity, int8_t input_sign_x, real_t acceleration_x, real_t deceleration_x, real_t turn_speed_x, real_t max_speed_x, real_t gravity);

	void jump(const Vector2& p_new_velocity);

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

	Player* player = nullptr;
	Sprite2D* player_sprite = nullptr;
	bool sprite_face_to_input = true;

	struct WalkSetting {
		real_t acceleration = 600.0;
		real_t deceleration = 5000.0;
		real_t turn_speed = 1200.0;
		real_t max_speed = 400.0;
	} walk_setting;

	struct JumpSetting {
		real_t height = 96.0;
		real_t duration = 0.4;
	} jump_setting;

	struct FallSetting {
		real_t gravity_multiplayer = 2.0;
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
