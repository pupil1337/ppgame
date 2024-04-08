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
	real_t walk_speed_change;

	// fall
	bool pressed_jump;
	bool desired_jump;
	uint8_t air_jump_time;
	real_t gravity_multiplier;

	// common
	Vector2i direct;
	Vector2 velocity;
	MovementMode movement_mode = MovementMode::Walk;

	// walk setting
	struct walk_setting {
		uint32_t max_speed = 1000;
		uint32_t acceleration = 500;
		uint32_t deceleration = 2000;
		uint32_t turn_speed = 2500;
	} walk_setting;

	// jump setting
	struct jump_setting {
		uint32_t height = 1000;
		real_t duration = 1.0;
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

protected:
	static void _bind_methods();
};

#endif // PLAYER_MOVEMENT_COMPONENT_H
