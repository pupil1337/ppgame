#ifndef PLAYER_MOVEMENT_COMPONENT_H
#define PLAYER_MOVEMENT_COMPONENT_H

#include <cstdint>
#include <godot_cpp/classes/wrapped.hpp>
#include <godot_cpp/core/defs.hpp>
#include <godot_cpp/variant/vector2.hpp>
using namespace godot;

#include "framework/component.h"

class Player;
class PlayerInputComponent;

class PlayerMovementComponent : public Component {
	GDCLASS(PlayerMovementComponent, Component)

public:
	virtual void _ready() override;
	virtual void _process(double delta) override;
	virtual void _physics_process(double delta) override;

private:
	int8_t _get_direct(real_t p_axis);

private:
	Player* player = nullptr;
	PlayerInputComponent* player_input_component = nullptr;

	int8_t direct_x;
	Vector2 desired_velocity;
	Vector2 velocity;
	real_t speed_change;

	// setting
	uint32_t max_speed = 1000;
	uint32_t acceleration = 500;
	uint32_t deceleration = 2000;
	uint32_t turn_speed = 2500;

	// ------------------------------------------

public:
	void set_max_speed(uint32_t p_max_speed);
	uint32_t get_max_speed();

	void set_acceleration(uint32_t p_acceleration);
	uint32_t get_acceleration();

	void set_deceleration(uint32_t p_deceleration);
	uint32_t get_deceleration();

	void set_turn_speed(uint32_t p_turn_speed);
	uint32_t get_turn_speed();

protected:
	static void _bind_methods();
};

#endif // PLAYER_MOVEMENT_COMPONENT_H
