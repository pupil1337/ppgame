#ifndef INPUT_TYPES_H
#define INPUT_TYPES_H

#include <godot_cpp/core/error_macros.hpp>
#include <godot_cpp/variant/string_name.hpp>
using namespace godot;

enum class InputAction {
	None = 0,

	Right = 1,
	Left = 2,
	Down = 3,
	Up = 4,
	Jump = 5,

	Max = 6

};

template <InputAction Type>
StringName InputActionName() {
	return StringName();
}
template <>
StringName InputActionName<InputAction::Right>() {
	return "Right";
}
template <>
StringName InputActionName<InputAction::Left>() {
	return "Left";
}
template <>
StringName InputActionName<InputAction::Down>() {
	return "Down";
}
template <>
StringName InputActionName<InputAction::Up>() {
	return "Up";
}
template <>
StringName InputActionName<InputAction::Jump>() {
	return "Jump";
}

namespace InputUtils {

template <InputAction Type>
StringName InputActionName() {
	switch (Type) {
		case InputAction::Right:
			return "Right";
		case InputAction::Left:
			return "Left";
		case InputAction::Down:
			return "Down";
		case InputAction::Up:
			return "Up";
		case InputAction::Jump:
			return "Jump";
		default:
			ERR_PRINT_ED("Utils::InputActionToStringName() 传入错误参数/方法未完全实现");
	}

	return "ERROR";
}

StringName InputAction_to_StringName(InputAction p_type) {
	switch (p_type) {
		case InputAction::Right:
			return "Right";
		case InputAction::Left:
			return "Left";
		case InputAction::Down:
			return "Down";
		case InputAction::Up:
			return "Up";
		case InputAction::Jump:
			return "Jump";
		default:
			ERR_PRINT_ED("Utils::InputActionToStringName() 传入错误参数/方法未完全实现");
	}

	return "ERROR";
}

} //namespace InputUtils

#endif // INPUT_TYPES_H
