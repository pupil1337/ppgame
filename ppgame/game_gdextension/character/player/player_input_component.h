#ifndef PLAYER_INPUT_COMPONENT_H
#define PLAYER_INPUT_COMPONENT_H

#include <godot_cpp/classes/input_event.hpp>
#include <godot_cpp/classes/ref.hpp>
#include <godot_cpp/classes/wrapped.hpp>
#include <godot_cpp/variant/vector2.hpp>
using namespace godot;

#include "framework/component.h"

class PlayerMovementComponent;

class PlayerInputComponent : public Component {
	GDCLASS(PlayerInputComponent, Component)

	friend PlayerMovementComponent;

private:
	Vector2 motion;

	// ------------------------------------------

public:
	virtual void _ready() override;
	virtual void _process(double delta) override;
	virtual void _unhandled_input(const Ref<InputEvent>& p_event) override;

protected:
	static void _bind_methods() {}
};

#endif // PLAYER_INPUT_COMPONENT_H
