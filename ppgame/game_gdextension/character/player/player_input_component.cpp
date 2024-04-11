#include "player_input_component.h"

#include <godot_cpp/classes/input.hpp>
#include <godot_cpp/variant/vector2.hpp>

Vector2 PlayerInputComponent::get_motion() {
	return Input::get_singleton()->get_vector("Left", "Right", "Up", "Down");
}

bool PlayerInputComponent::get_just_pressed_jump() {
	return Input::get_singleton()->is_action_just_pressed("Jump");
}
