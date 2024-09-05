#include "actor.h"

#include <godot_cpp/classes/node.hpp>
#include <godot_cpp/core/error_macros.hpp>
#include <godot_cpp/templates/hash_map.hpp>
#include <godot_cpp/variant/string.hpp>
#include <godot_cpp/variant/string_name.hpp>
#include <godot_cpp/variant/utility_functions.hpp>

#include "framework/component.h"

bool Actor::add_component(Component* p_component) {
	ERR_FAIL_NULL_V_EDMSG(p_component, false, "Actor add a nullptr component");
	StringName component_name = p_component->get_class();
	ERR_FAIL_COND_V_EDMSG(components.has(component_name), false, "Actor try to re-add component");
	components.insert(component_name, p_component);
	return true;
}

Actor* Actor::get_parent_actor(Node* p_node) {
	if (p_node) {
		if (Node* parent = p_node->get_parent()) {
			if (parent != p_node) {
				if (Actor* actor = dynamic_cast<Actor*>(parent)) {
					return actor;
				} else {
					return get_parent_actor(parent);
				}
			}
		}
	}

	return nullptr;
}
