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

public:
	_FORCE_INLINE_ Vector2 get_motion() { return motion; }
	_FORCE_INLINE_ bool get_pressed_jump() { return pressed_jump; }

private:
	Vector2 motion;
	bool pressed_jump = false;

	// ------------------------------------------

public:
	virtual void _process(double delta) override;
	virtual void _unhandled_input(const Ref<InputEvent>& p_event) override;

protected:
	static void _bind_methods() {}
};

#endif // PLAYER_INPUT_COMPONENT_H
