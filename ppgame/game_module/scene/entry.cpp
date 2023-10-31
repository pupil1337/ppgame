#include "entry.h"

#include <scene/main/window.h>
#include "system/multiplayerSystem.h"
#include "gui/menu/menu_main.h"

void Entry::_bind_methods() {
	PP_ADD_PROPERTY(Variant::OBJECT, scene_menu_main, PROPERTY_HINT_RESOURCE_TYPE, "PackedScene")
}

void Entry::_notification(int p_notification) {
	switch (p_notification) {
		case NOTIFICATION_ENTER_TREE: {
			if (!Engine::get_singleton()->is_editor_hint()) {
				_enter_tree();
			}
		} break;
	}
}

void Entry::_enter_tree() {
	initialize_system();
	open_menu_main();
}

void Entry::initialize_system() {
	MultiplayerSystem* multiplayerSystem = memnew(MultiplayerSystem);
	get_tree()->get_root()->add_child(multiplayerSystem);
	print_line(multiplayerSystem);
}

void Entry::open_menu_main() {
	if (scene_menu_main.is_valid()) {
		MenuMain* menu_main = Object::cast_to<MenuMain>(scene_menu_main->instantiate());
		get_tree()->get_root()->add_child(menu_main);
		print_line(menu_main);
	}
}
