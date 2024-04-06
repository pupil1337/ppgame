#include "component.h"

#include <functional>
#include <godot_cpp/classes/node.hpp>

#include "framework/actor.h"

void Component::_enter_tree() {
	std::function<void(Node * p_node)> _register_component;
	_register_component = [&_register_component, this](Node* p_node) -> void {
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
	};

	_register_component(this);
}
