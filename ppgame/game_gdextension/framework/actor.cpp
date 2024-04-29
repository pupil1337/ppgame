#include "actor.h"

#include <godot_cpp/core/error_macros.hpp>
#include <godot_cpp/templates/hash_map.hpp>
#include <godot_cpp/variant/string.hpp>
#include <godot_cpp/variant/string_name.hpp>
#include <godot_cpp/variant/utility_functions.hpp>

#include "framework/component.h"

void Actor::add_component(Component* p_component) {
	StringName component_name = p_component->get_class();
	ERR_FAIL_COND_EDMSG(components.has(component_name), "Try to re-add component");
	components.insert(component_name, p_component);
}
