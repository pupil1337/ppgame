#include "game.h"

#include "scene/gui/menu/menu_main.h"
#include "scene/world.h"
#include "system/multiplayerSystem.h"

void Game::_bind_methods() {
	PP_ADD_PROPERTY(Variant::OBJECT, menu_main, PROPERTY_HINT_NODE_TYPE, "MenuMain");
	PP_ADD_PROPERTY(Variant::OBJECT, packed_scene_world, PROPERTY_HINT_RESOURCE_TYPE, "PackedScene");
}

void Game::_on_start_button_pressed() {
	MultiplayerSystem::get_singleton()->hostGame();

	ERR_FAIL_NULL_EDMSG(packed_scene_world.ptr(), "not set packed_scene world");
	World* world = Object::cast_to<World>(packed_scene_world->instantiate());
	add_child(world);

	menu_main->hide();
}

void Game::_on_join_button_pressed() {
	MultiplayerSystem::get_singleton()->joinGame();

	ERR_FAIL_NULL_EDMSG(packed_scene_world.ptr(), "not set packed_scene world");
	World* world = Object::cast_to<World>(packed_scene_world->instantiate());
	add_child(world);

	menu_main->hide();
}
