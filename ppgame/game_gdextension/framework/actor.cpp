#include "actor.h"

#include <godot_cpp/templates/hash_map.hpp>
#include <godot_cpp/variant/string.hpp>

#include "framework/component.h"

void Actor::add_component(Component* p_component) {
	Components.insert(p_component->get_class(), p_component);
}

void Actor::initialize_components() {
	for (HashMap<StringName, Component*>::Iterator i = Components.begin(); i != Components.end(); ++i) {
		if (i->value) {
			i->value->initialize_component();
		}
	}
}
