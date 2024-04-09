#ifndef PLAYER_MOVEMENT_COMPONENT_H
#define PLAYER_MOVEMENT_COMPONENT_H

#include <cstdint>
#include <godot_cpp/classes/wrapped.hpp>
#include <godot_cpp/core/defs.hpp>
#include <godot_cpp/variant/vector2.hpp>
#include <godot_cpp/variant/vector2i.hpp>
using namespace godot;

#include "framework/component.h"

class Player;
class PlayerInputComponent;

class PlayerMovementComponent : public Component {
	GDCLASS(PlayerMovementComponent, Component)

public:
	void move_x(double delta);
	void move_y(double delta);

	// TODO 删除以下

public:
	void jump();
	void stop_jumping();

private:
	enum MovementMode {
		Walk,
		Fall
	};

	void physics_walk(double delta);
	void physics_fall(double delta);

	int8_t _get_direct(real_t p_axis);

	bool _can_jump();
	void _do_jump();
	void _calculate_gravity();

private:
	Player* player = nullptr;
	PlayerInputComponent* player_input_component = nullptr;

	// walk
	real_t desired_walk_velocity;

	// fall
	bool pressed_jump = false;
	bool desired_jump = false;
	uint8_t air_jump_time;

	// common
	Vector2i direct;
	Vector2 velocity;
	real_t gravity;
	MovementMode movement_mode = MovementMode::Walk;

	// walk setting
	struct walk_setting {
		uint32_t max_speed = 400;
		uint32_t acceleration = 600;
		uint32_t deceleration = 5000;
		uint32_t turn_speed = 1200;
	} walk_setting;

	// jump setting
	struct jump_setting {
		uint32_t height = 96;
		real_t duration = 0.3;
		real_t fall_gravity_multiplier = 2.0;
		uint8_t air_jump_time = 0;
	} jump_setting;

	// ------------------------------------------

public:
	virtual void _ready() override;
	virtual void _process(double delta) override;
	virtual void _physics_process(double delta) override;

private:
	void set_walk_max_speed(uint32_t p_max_speed);
	uint32_t get_walk_max_speed();

	void set_walk_acceleration(uint32_t p_acceleration);
	uint32_t get_walk_acceleration();

	void set_walk_deceleration(uint32_t p_deceleration);
	uint32_t get_walk_deceleration();

	void set_walk_turn_speed(uint32_t p_turn_speed);
	uint32_t get_walk_turn_speed();

	void set_jump_height(uint32_t p_height);
	uint32_t get_jump_height();

	void set_jump_duration(real_t p_duration);
	real_t get_jump_duration();

	void set_jump_fall_gravity_multiplier(real_t p_fall_gravity_multiplier);
	real_t get_jump_fall_gravity_multiplier();

	void set_jump_air_jump_time(uint8_t p_air_jump_time);
	uint8_t get_jump_air_jump_time();

protected:
	static void _bind_methods();
};

#endif // PLAYER_MOVEMENT_COMPONENT_H
