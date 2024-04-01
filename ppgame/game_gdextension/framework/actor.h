#ifndef ACTOR_H
#define ACTOR_H

#include <godot_cpp/classes/object.hpp>
#include <godot_cpp/templates/hash_map.hpp>
using namespace godot;

namespace godot {
class StringName;
}
class Component;

class Actor {
	friend Component;

private:
	void add_component(Component* p_component);

protected:
	void initialize_components();

public:
	template <typename T>
	T* get_component() const {
		return Object::cast_to<T>(Components.find(T::get_class_static())->value);
	}

private:
	HashMap<StringName, Component*> Components;
};

#endif // ACTOR_H
