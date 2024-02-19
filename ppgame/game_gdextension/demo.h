#ifndef GAME_H
#define GAME_H

#include "godot_cpp/classes/node.hpp"
#include "godot_cpp/classes/packed_scene.hpp"
using namespace godot;

class Demo : public Node {
	GDCLASS(Demo, Node)

protected:
	static void _bind_methods();

private:
	Node* node = nullptr;
	Ref<PackedScene> packed_scene_world;

public:
	_FORCE_INLINE_ Node* get_node() const { return node; }
	_FORCE_INLINE_ Ref<PackedScene> get_packed_scene_world() const { return packed_scene_world; }
	void set_node(Node* p_node);
	void set_packed_scene_world(const Ref<PackedScene>& p_packed_scene_world);

	// ------------------------------------------

public:
	void _func1();
	void _func2();
};

#endif // GAME_H
