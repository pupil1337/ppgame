#ifndef ENTRY_H
#define ENTRY_H

#include <scene/main/node.h>
#include <scene/resources/packed_scene.h>
#include "base/pp.h"

class Entry : public Node {
	GDCLASS(Entry, Node)

protected:
	static void _bind_methods();
	void _notification(int p_notification);

//~Begin This Class
private:
	void _enter_tree();

	void initialize_system();
	void open_menu_main();

	PP_PROPERTY(Ref<PackedScene>, scene_menu_main, {})
};

#endif // ENTRY_H
