#include "entry.h"

#include "system/multiplayerSystem.h"
#include "gui/menu/menu_main.h"

void Entry::_bind_methods() {
	PP_ADD_PROPERTY(Variant::OBJECT, scene_menu_main, PROPERTY_HINT_RESOURCE_TYPE, "PackedScene");
}

void Entry::_enter_tree() {
	PP_CONTINUE_IF_GAME

	initialize_system();
	open_menu_main();
}

void Entry::initialize_system() {
	MultiplayerSystem* multiplayerSystem = memnew(MultiplayerSystem);
	get_tree()->get_root()->add_child(multiplayerSystem);
	UtilityFunctions::print(multiplayerSystem);
}

void Entry::open_menu_main() {
	if (scene_menu_main.is_valid()) {
		MenuMain* menu_main = Object::cast_to<MenuMain>(scene_menu_main->instantiate());
		get_tree()->get_root()->add_child(menu_main);
		UtilityFunctions::print(menu_main);
	}
}
