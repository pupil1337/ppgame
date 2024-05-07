#include "door.h"

#include <godot_cpp/classes/engine.hpp>
#include <godot_cpp/classes/node2d.hpp>
#include <godot_cpp/variant/callable_method_pointer.hpp>
#include <godot_cpp/variant/utility_functions.hpp>

Door::Door() {
	if (!Engine::get_singleton()->is_editor_hint()) {
		connect("body_entered", callable_mp(this, &self_type::_body_entered));
	}
}

void Door::_enter_tree() {
	parent_type::_enter_tree();
}

void Door::_body_entered(Node2D* p_body) {
	UtilityFunctions::print("door::_body_entered: ", p_body->get_name());
}
