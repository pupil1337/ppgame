#include "demo_gdextension.h"

#include <godot_cpp/classes/engine.hpp>
#include <godot_cpp/variant/utility_functions.hpp>

void DemoGdextension::_ready() {
	parent_type::_ready();

	UtilityFunctions::print("DemoGdextension _ready: editor/game");
}
void DemoGdextension::_process(double delta) {
	parent_type::_process(delta);

	if (!Engine::get_singleton()->is_editor_hint()) {
		UtilityFunctions::print("DemoGdextension _process: game, and delta = ", delta);
	}
}
