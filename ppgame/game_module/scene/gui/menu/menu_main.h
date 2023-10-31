#ifndef MENU_MAIN_H
#define MENU_MAIN_H

#include <scene/gui/control.h>

#include "base/pp.h"

class Button;


class MenuMain : public Control {
	GDCLASS(MenuMain, Control)

protected:
	static void _bind_methods();
	void _notification(int p_notification);

//~Begin This Class
private:
	void _ready();

	void _on_start_button_pressed();
	void _on_join_button_pressed();

	PP_PROPERTY(Button*, start_button, nullptr)
	PP_PROPERTY(Button*, join_button, nullptr)
};

#endif // MENU_MAIN_H
