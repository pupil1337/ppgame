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

#endif // INPUT_TYPES_H
