#include "player_input_component.h"
#include "godot_cpp/variant/utility_functions.hpp"

#include <godot_cpp/classes/input.hpp>
#include <godot_cpp/classes/input_event.hpp>
#include <godot_cpp/classes/ref.hpp>
#include <godot_cpp/variant/vector2.hpp>

void PlayerInputComponent::_ready() {
}

void PlayerInputComponent::_process(double delta) {
	motion = Input::get_singleton()->get_vector("Left", "Right", "Up", "Down");
	UtilityFunctions::print("input::", motion);
}

void PlayerInputComponent::_unhandled_input(const Ref<InputEvent>& p_event) {
	if (p_event->is_action("Jump")) {
		if (p_event->is_pressed()) {
			if (!p_event->is_echo()) {
			}
		} else /* if (p_event->is_released()) */ {
		}
	}
}
