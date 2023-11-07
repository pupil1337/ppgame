#ifndef MENU_MAIN_H
#define MENU_MAIN_H

using namespace godot;

class MenuMain : public Control {
	GDCLASS(MenuMain, Control)

protected:
	static void _bind_methods();

public:
	virtual void _ready() override;

	//~Begin This Class
private:
	PP_PROPERTY(Button*, start_button) = nullptr;
	PP_PROPERTY(Button*, join_button) = nullptr;
};

#endif // MENU_MAIN_H
