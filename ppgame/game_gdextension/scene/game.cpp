#include "game.h"

#include "scene/gui/menu/menu_main.h"
#include "scene/world.h"
#include "system/multiplayerSystem.h"

void Game::_bind_methods() {
	// menu_main
	ClassDB::bind_method(D_METHOD(_STR(set_menu_main), _STR(menu_main)), &self_type::set_menu_main);
	ClassDB::bind_method(D_METHOD(_STR(get_menu_main)), &self_type::get_menu_main);
	ADD_PROPERTY(PropertyInfo(Variant::OBJECT, _STR(menu_main), PROPERTY_HINT_NODE_TYPE, "MenuMain"), _STR(set_menu_main), _STR(get_menu_main));

	// packed_scene_world
	ClassDB::bind_method(D_METHOD(_STR(set_packed_scene_world), _STR(packed_scene_world)), &self_type::set_packed_scene_world);
	ClassDB::bind_method(D_METHOD(_STR(get_packed_scene_world)), &self_type::get_packed_scene_world);
	ADD_PROPERTY(PropertyInfo(Variant::OBJECT, _STR(packed_scene_world), PROPERTY_HINT_RESOURCE_TYPE, "PackedScene"), _STR(set_packed_scene_world), _STR(get_packed_scene_world));
}

void Game::set_menu_main(MenuMain* p_menu_main) {
	menu_main = p_menu_main;
}

void Game::set_packed_scene_world(const Ref<PackedScene>& p_packed_scene_world) {
	packed_scene_world = p_packed_scene_world;
}

// ----------------------------------------------------------------------------

void Game::_on_start_button_pressed() {
	MultiplayerSystem::hostGame();

	ERR_FAIL_NULL_EDMSG(packed_scene_world.ptr(), "not set packed_scene world");
	World* world = Object::cast_to<World>(packed_scene_world.ptr()->instantiate());
	add_child(world);

	ERR_FAIL_NULL(menu_main);
	menu_main->hide();
}

void Game::_on_join_button_pressed() {
	MultiplayerSystem::joinGame();

	ERR_FAIL_NULL_EDMSG(packed_scene_world.ptr(), "not set packed_scene world");
	World* world = Object::cast_to<World>(packed_scene_world.ptr()->instantiate());
	add_child(world);

	ERR_FAIL_NULL(menu_main);
	menu_main->hide();
}
