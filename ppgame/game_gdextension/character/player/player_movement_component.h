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
	typedef Component super;

public:
	void input_move(double delta, Vector2 curr_velocity, int8_t input_sign_x, real_t acceleration_x, real_t deceleration_x, real_t turn_speed_x, real_t max_speed_x, real_t gravity);

private:
	Player* player = nullptr;
	Sprite2D* player_sprite = nullptr;
	bool sprite_face_to_input = true;

	// ------------------------------------------

public:
	virtual void _ready() override;

protected:
	static void _bind_methods() {}
};

#endif // PLAYER_MOVEMENT_COMPONENT_H
