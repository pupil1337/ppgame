#include "actor.h"

#include <godot_cpp/templates/hash_map.hpp>
#include <godot_cpp/variant/string.hpp>

#include "framework/component.h"
#include "godot_cpp/variant/utility_functions.hpp"

void Actor::add_component(Component* p_component) {
	components.insert(p_component->get_class(), p_component);

	UtilityFunctions::print("Actor::add_component(", p_component->get_class(), ").");
}
