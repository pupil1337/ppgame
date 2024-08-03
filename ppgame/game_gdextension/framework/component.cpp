#include "component.h"

#include <godot_cpp/classes/engine.hpp>
#include <godot_cpp/classes/node.hpp>
#include <godot_cpp/core/error_macros.hpp>

#include "framework/actor.h"

void Component::_notification(int p_what) {
	if (!Engine::get_singleton()->is_editor_hint()) {
		if (p_what == NOTIFICATION_PARENTED) {
			if (!_register_component(this)) {
				ERR_PRINT_ED("_register_component->" + get_class());
			}
		}
	}
}

bool Component::_register_component(Node* p_node) {
	if (p_node) {
		if (Node* parent = p_node->get_parent()) {
			if (parent != p_node) {
				actor = dynamic_cast<Actor*>(parent);
				if (actor != nullptr) {
					return actor->add_component(this);
				} else {
					return _register_component(parent);
				}
			}
		}
	}

	return false;
}
