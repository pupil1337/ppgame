#include "player_input_component.h"

#include <godot_cpp/classes/engine.hpp>
#include <godot_cpp/classes/input.hpp>
#include <godot_cpp/variant/vector2.hpp>

#include "utils/input_string_names.h"
#include "utils/math_utils.h"

void PlayerInputComponent::_process(double delta) {
	parent_type::_process(delta);

	if (!Engine::get_singleton()->is_editor_hint()) {
		Input* input = Input::get_singleton();
		// motion
		motion = input->get_vector(InputStringName(Left), InputStringName(Right), InputStringName(Up), InputStringName(Down));

		// sign_x, sign_y
		MathUtils::get_direction_sign(motion, sign_x, sign_y);

		// just_pressed_jump
		just_pressed_jump = input->is_action_just_pressed(InputStringName(Jump));

		// just_pressed_attack
		just_pressed_attack = input->is_action_just_pressed(InputStringName(Attack));
	}
}
