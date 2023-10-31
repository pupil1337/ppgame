#ifndef MENU_MAIN_H
#define MENU_MAIN_H

#include <godot_cpp/classes/control.hpp>
#include <godot_cpp/classes/button.hpp>

#include "pp.h"

using namespace godot;

class MenuMain : public Control {
	GDCLASS(MenuMain, Control)

protected:
	static void _bind_methods();

public:
	virtual void _ready() override;

//~Begin This Class
private:
	void _on_start_button_pressed();
	void _on_join_button_pressed();

	PP_PROPERTY(Button*, start_button, nullptr)
	PP_PROPERTY(Button*, join_button, nullptr)
};

#endif // MENU_MAIN_H
