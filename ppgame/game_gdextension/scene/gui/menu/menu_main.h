#ifndef MENU_MAIN_H
#define MENU_MAIN_H

using namespace godot;

class MenuMain : public Control {
	GDCLASS(MenuMain, Control)

protected:
	static void _bind_methods();

private:
	Button* start_button = nullptr;
	Button* join_button = nullptr;

public:
	_FORCE_INLINE_ Button* get_start_button() const { return start_button; }
	_FORCE_INLINE_ Button* get_join_button() const { return join_button; }
	void set_start_button(Button* p_start_button);
	void set_join_button(Button* p_join_button);

	// ------------------------------------------

public:
	virtual void _ready() override;
};

#endif // MENU_MAIN_H
