#ifndef ENTRY_H
#define ENTRY_H

#include <godot_cpp/classes/node.hpp>
#include <godot_cpp/classes/packed_scene.hpp>

#include "pp.h"

using namespace godot;

class Entry : public Node {
	GDCLASS(Entry, Node)

protected:
	static void _bind_methods();

public:
	virtual void _enter_tree() override;

//~Begin This Class
private:
	void initialize_system();
	void open_menu_main();

	PP_PROPERTY(Ref<PackedScene>, scene_menu_main, {})
};

#endif // ENTRY_H
