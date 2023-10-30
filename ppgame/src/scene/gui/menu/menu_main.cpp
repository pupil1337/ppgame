#include "menu_main.h"

#include <scene/gui/button.h>
#include <scene/resources/packed_scene.h>
#include <scene/main/window.h>

void MenuMain::_bind_methods() {
	PP_ADD_PROPERTY(Variant::OBJECT, start_button, PROPERTY_HINT_NODE_TYPE, "Button")
	PP_ADD_PROPERTY(Variant::OBJECT, join_button, PROPERTY_HINT_NODE_TYPE, "Button")
}

void MenuMain::_notification(int p_notification) {
	switch (p_notification) {
		case NOTIFICATION_READY: {
			if (!Engine::get_singleton()->is_editor_hint()) {
				_ready();
			}
		} break;
	}
}

void MenuMain::_ready() {
	if (start_button) {
		start_button->connect(SNAME("pressed"), callable_mp(this, &MenuMain::_on_start_button_pressed));
	}

	if (join_button) {
		join_button->connect(SNAME("pressed"), callable_mp(this, &MenuMain::_on_join_button_pressed));
	}
}

void MenuMain::_on_start_button_pressed() {
	print_line("start_button pressed!");

	Ref<PackedScene> Map = ResourceLoader::load("res://scene/level/main.tscn", "PackedScene");
	if (Map.is_valid()) {
		get_tree()->get_root()->add_child(Map->instantiate());
		hide();
	}
}

void MenuMain::_on_join_button_pressed() {
	print_line("join_button pressed!");
}
