#include "component.h"

#include <functional>
#include <godot_cpp/classes/node.hpp>

#include "framework/actor.h"

void Component::_enter_tree() {
	std::function<Actor*(Node * p_node)> _get_owner_actor;
	_get_owner_actor = [&_get_owner_actor](Node* p_node) -> Actor* {
		if (p_node) {
			if (Node* parent = p_node->get_parent()) {
				if (parent != p_node) {
					if (Actor* actor = dynamic_cast<Actor*>(parent)) {
						return actor;
					}
					return _get_owner_actor(parent);
				}
			}
		}

		return nullptr;
	};

	if (Actor* actor = _get_owner_actor(this)) {
		actor->add_component(this);
	}
}
