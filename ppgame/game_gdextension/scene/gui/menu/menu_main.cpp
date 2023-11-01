#include "menu_main.h"

#include "system/multiplayerSystem.h"

void MenuMain::_bind_methods() {
	PP_ADD_PROPERTY(Variant::OBJECT, start_button, PROPERTY_HINT_NODE_TYPE, "Button");
	PP_ADD_PROPERTY(Variant::OBJECT, join_button, PROPERTY_HINT_NODE_TYPE, "Button");
}

void MenuMain::_ready() {
	PP_CONTINUE_IF_GAME

	if (start_button) {
		start_button->connect("pressed", callable_mp(this, &MenuMain::_on_start_button_pressed));
	}
	if (join_button) {
		join_button->connect("pressed", callable_mp(this, &MenuMain::_on_join_button_pressed));
	}
}

void MenuMain::_on_start_button_pressed() {
	MultiplayerSystem::get_singleton()->HostGame();
	queue_free();
}

void MenuMain::_on_join_button_pressed() {
	MultiplayerSystem::get_singleton()->JoinGame();
	queue_free();
}
