#include "menu_main.h"

#include "scene/game.h"

void MenuMain::_bind_methods() {
	// start_button
	ClassDB::bind_method(D_METHOD(_STR(set_start_button), _STR(start_button)), &self_type::set_start_button);
	ClassDB::bind_method(D_METHOD(_STR(get_start_button)), &self_type::get_start_button);
	ADD_PROPERTY(PropertyInfo(Variant::OBJECT, _STR(start_button), PROPERTY_HINT_NODE_TYPE, "Button"), _STR(set_start_button), _STR(get_start_button));

	// join_button
	ClassDB::bind_method(D_METHOD(_STR(set_join_button), _STR(join_button)), &self_type::set_join_button);
	ClassDB::bind_method(D_METHOD(_STR(get_join_button)), &self_type::get_join_button);
	ADD_PROPERTY(PropertyInfo(Variant::OBJECT, _STR(join_button), PROPERTY_HINT_NODE_TYPE, "Button"), _STR(set_join_button), _STR(get_join_button));
}

void MenuMain::set_start_button(Button* p_start_button) {
	start_button = p_start_button;
}

void MenuMain::set_join_button(Button* p_join_button) {
	join_button = p_join_button;
}

// ----------------------------------------------------------------------------

void MenuMain::_ready() {
	PP_CONTINUE_IF_GAME

	ERR_FAIL_NULL(start_button);
	start_button->connect("pressed", callable_mp(Object::cast_to<Game>(get_parent()), &Game::_on_start_button_pressed));

	ERR_FAIL_NULL(join_button);
	join_button->connect("pressed", callable_mp(Object::cast_to<Game>(get_parent()), &Game::_on_join_button_pressed));
}
