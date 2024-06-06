#include "input_string_names.h"

InputStringNames* InputStringNames::singleton = nullptr;

InputStringNames::InputStringNames() :
		Left("Left"),
		Right("Right"),
		Up("Up"),
		Down("Down"),
		Jump("Jump"),
		Attack("Attack") {
}
