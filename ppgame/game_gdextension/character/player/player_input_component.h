#ifndef PLAYER_INPUT_COMPONENT_H
#define PLAYER_INPUT_COMPONENT_H

#include <godot_cpp/classes/input_event.hpp>
#include <godot_cpp/classes/ref.hpp>
#include <godot_cpp/classes/wrapped.hpp>
#include <godot_cpp/core/defs.hpp>
#include <godot_cpp/variant/vector2.hpp>
using namespace godot;

#include "framework/component.h"

class PlayerInputComponent : public Component {
	GDCLASS(PlayerInputComponent, Component)
	typedef Component super;

public:
	Vector2 get_motion();
	bool get_just_pressed_jump();

	// ------------------------------------------

protected:
	static void _bind_methods() {}
};

#endif // PLAYER_INPUT_COMPONENT_H
