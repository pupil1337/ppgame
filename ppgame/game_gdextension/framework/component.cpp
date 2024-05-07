#include "component.h"

#include <godot_cpp/classes/engine.hpp>
#include <godot_cpp/classes/node.hpp>

#include "framework/actor.h"

void Component::_enter_tree() {
	parent_type::_enter_tree();

	if (!Engine::get_singleton()->is_editor_hint()) {
		_register_component(this);
	}
}

void Component::_register_component(Node* p_node) {
	if (p_node) {
		if (Node* parent = p_node->get_parent()) {
			if (parent != p_node) {
				actor = dynamic_cast<Actor*>(parent);
				if (actor) {
					actor->add_component(this);
				} else {
					_register_component(parent);
				}
			}
		}
	}
}
