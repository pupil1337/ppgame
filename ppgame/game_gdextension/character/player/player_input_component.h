#ifndef PLAYER_INPUT_COMPONENT_H
#define PLAYER_INPUT_COMPONENT_H

#include <cstdint>
#include <godot_cpp/classes/input_event.hpp>
#include <godot_cpp/classes/ref.hpp>
#include <godot_cpp/classes/wrapped.hpp>
#include <godot_cpp/core/defs.hpp>
#include <godot_cpp/variant/vector2.hpp>
using namespace godot;

#include "framework/component.h"

class PlayerInputComponent : public Component {
	GDCLASS(PlayerInputComponent, Component)

public:
	_FORCE_INLINE_ Vector2 get_motion() { return motion; }
	_FORCE_INLINE_ int8_t get_sign_x() { return sign_x; }
	_FORCE_INLINE_ int8_t get_sign_y() { return sign_y; }
	_FORCE_INLINE_ bool get_just_pressed_jump() { return just_pressed_jump; }

private:
	Vector2 motion;
	int8_t sign_x = 0;
	int8_t sign_y = 0;
	bool just_pressed_jump = false;

	// ------------------------------------------

public:
	void _process(double delta) override;

protected:
	static void _bind_methods() {}
};

#endif // PLAYER_INPUT_COMPONENT_H
