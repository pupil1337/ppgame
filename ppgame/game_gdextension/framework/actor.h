#ifndef ACTOR_H
#define ACTOR_H

#include <godot_cpp/classes/object.hpp>
#include <godot_cpp/templates/hash_map.hpp>
#include <godot_cpp/variant/string_name.hpp>
using namespace godot;

class Component;

class Actor {
	friend Component;

public:
	template <typename T>
	T* get_component() const {
		return Object::cast_to<T>(components.find(T::get_class_static())->value);
	}

private:
	void add_component(Component* p_component);

private:
	HashMap<StringName, Component*> components;
};

#endif // ACTOR_H
