#include "player.h"

#include <godot_cpp/classes/engine.hpp>

void Playertest::_bind_methods() {
}

void Playertest::_ready() {
	CharacterBody2D::_ready();

	if (!Engine::get_singleton()->is_editor_hint()) {
		ERR_FAIL_EDMSG("这是个测试用222");
	}
}
