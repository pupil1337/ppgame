#include "demo.h"

void Demo::_bind_methods() {
	// node
	ClassDB::bind_method(D_METHOD(_STR(set_node), _STR(node)), &self_type::set_node);
	ClassDB::bind_method(D_METHOD(_STR(get_node)), &self_type::get_node);
	ADD_PROPERTY(PropertyInfo(Variant::OBJECT, _STR(node), PROPERTY_HINT_NODE_TYPE, "Node"), _STR(set_node), _STR(get_node));

	// packed_scene_world
	ClassDB::bind_method(D_METHOD(_STR(set_packed_scene_world), _STR(packed_scene_world)), &self_type::set_packed_scene_world);
	ClassDB::bind_method(D_METHOD(_STR(get_packed_scene_world)), &self_type::get_packed_scene_world);
	ADD_PROPERTY(PropertyInfo(Variant::OBJECT, _STR(packed_scene_world), PROPERTY_HINT_RESOURCE_TYPE, "PackedScene"), _STR(set_packed_scene_world), _STR(get_packed_scene_world));
}

void Demo::set_node(Node* p_node) {
	node = p_node;
}

void Demo::set_packed_scene_world(const Ref<PackedScene>& p_packed_scene_world) {
	packed_scene_world = p_packed_scene_world;
}

// ----------------------------------------------------------------------------

void Demo::_func1() {
}

void Demo::_func2() {
}
