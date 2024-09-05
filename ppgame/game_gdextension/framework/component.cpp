#include "component.h"

#include <godot_cpp/classes/engine.hpp>
#include <godot_cpp/classes/node.hpp>
#include <godot_cpp/core/error_macros.hpp>

#include "framework/actor.h"

void Component::_notification(int p_what) {
	if (!Engine::get_singleton()->is_editor_hint()) {
		if (p_what == NOTIFICATION_PARENTED) {
			actor = Actor::get_parent_actor(this);
			if (!actor || !actor->add_component(this)) {
				ERR_PRINT_ED("_register_component->" + get_class());
			}
		}
	}
}
