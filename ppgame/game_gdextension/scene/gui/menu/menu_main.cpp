#include "menu_main.h"

#include "scene/game.h"

void MenuMain::_bind_methods() {
	PP_ADD_PROPERTY(Variant::OBJECT, start_button, PROPERTY_HINT_NODE_TYPE, "Button");
	PP_ADD_PROPERTY(Variant::OBJECT, join_button, PROPERTY_HINT_NODE_TYPE, "Button");
}

void MenuMain::_ready() {
	PP_CONTINUE_IF_GAME

	if (start_button) {
		start_button->connect("pressed", callable_mp(Object::cast_to<Game>(get_parent()), &Game::_on_start_button_pressed));
	}
	if (join_button) {
		join_button->connect("pressed", callable_mp(Object::cast_to<Game>(get_parent()), &Game::_on_join_button_pressed));
	}
}
