#include "controller.h"

#include <godot_cpp/classes/input.hpp>
#include <godot_cpp/classes/input_event.hpp>
#include <godot_cpp/classes/ref.hpp>
#include <godot_cpp/variant/string_name.hpp>
#include <godot_cpp/variant/utility_functions.hpp>
#include <godot_cpp/variant/vector2.hpp>

#include "controller/command/controller_command.h"
#include "framework/command.h"

void Controller::_process(double delta) {
	handle_input();
}

void Controller::handle_input() {
	handle_input_motion();
}

void Controller::handle_input_motion() {
	Vector2 Motion = Input::get_singleton()->get_vector("Left", "Right", "Up", "Down");
	Command* command = new ControllerMotionCommand(Motion.x, Motion.y);
	command->execute(nullptr);
}

void Controller::_unhandled_input(const Ref<InputEvent>& p_event) {
	static ControllerJumpCommand jump_command;

	//jump_command.execute(nullptr);
	// for (int i = (int)InputAction::None + 1; i < (int)InputAction::Max; ++i) {
	// 	auto aa = InputUtils::InputActionName<(InputAction)0>();
	// 	const StringName& ActionName = InputUtils::InputAction_to_StringName((InputAction)i);
	// 	if (p_event->is_action(ActionName, true)) {
	// 		UtilityFunctions::print("----------------------------------------");
	// 		// UtilityFunctions::print("[Controller]input::" + ActionName);
	// 		UtilityFunctions::print("is_pressed:", index, p_event->is_pressed() ? "true" : "false");
	// 		// UtilityFunctions::print("is_canceled:", p_event->is_canceled() ? "true" : "false");
	// 		UtilityFunctions::print("is_released:", index, p_event->is_released() ? "true" : "false");
	// 		UtilityFunctions::print("is_echo:", p_event->is_echo() ? "true" : "false");
	// 	}
	// }
}
