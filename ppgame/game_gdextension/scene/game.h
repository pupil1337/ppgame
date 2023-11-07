#ifndef GAME_H
#define GAME_H

using namespace godot;

class MenuMain;

class Game : public Node {
	GDCLASS(Game, Node)

protected:
	static void _bind_methods();

	//~Begin This Class
public:
	void _on_start_button_pressed();
	void _on_join_button_pressed();

private:
	PP_PROPERTY(MenuMain*, menu_main) = nullptr;
	PP_PROPERTY(Ref<PackedScene>, packed_scene_world) = Ref<PackedScene>();
};

#endif // GAME_H
