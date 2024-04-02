#include "controller.h"

#include <godot_cpp/classes/input.hpp>
#include <godot_cpp/classes/input_event.hpp>
#include <godot_cpp/classes/ref.hpp>
#include <godot_cpp/variant/string_name.hpp>
#include <godot_cpp/variant/utility_functions.hpp>

#include "input/input_enums.h"

void Controller::_process(double delta) {
	if (Input::get_singleton()->is_action_just_pressed(InputActionName<InputAction::Jump>())) {
		UtilityFunctions::print("is_action_just_pressed ", index);
	}
	if (Input::get_singleton()->is_action_just_released(InputActionName<InputAction::Jump>())) {
		UtilityFunctions::print("is_action_just_released ", index);
	}

	if (Input::get_singleton()->is_action_pressed(InputActionName<InputAction::Jump>())) {
		UtilityFunctions::print("is_action_pressed ", index);
	}

	++index;

	// TODO connect & emit_signal
}

void Controller::_unhandled_input(const Ref<InputEvent>& p_event) {
	for (int i = (int)InputAction::None + 1; i < (int)InputAction::Max; ++i) {
		auto aa = InputUtils::InputActionName<(InputAction)0>();
		const StringName& ActionName = InputUtils::InputAction_to_StringName((InputAction)i);
		if (p_event->is_action(ActionName, true)) {
			UtilityFunctions::print("----------------------------------------");
			// UtilityFunctions::print("[Controller]input::" + ActionName);
			UtilityFunctions::print("is_pressed:", index, p_event->is_pressed() ? "true" : "false");
			// UtilityFunctions::print("is_canceled:", p_event->is_canceled() ? "true" : "false");
			UtilityFunctions::print("is_released:", index, p_event->is_released() ? "true" : "false");
			UtilityFunctions::print("is_echo:", p_event->is_echo() ? "true" : "false");
		}
	}
}
