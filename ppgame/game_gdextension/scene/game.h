#ifndef GAME_H
#define GAME_H

using namespace godot;

class MenuMain;

class Game : public Node {
	GDCLASS(Game, Node)

protected:
	static void _bind_methods();

private:
	MenuMain* menu_main = nullptr;
	Ref<PackedScene> packed_scene_world;

public:
	_FORCE_INLINE_ MenuMain* get_menu_main() const { return menu_main; }
	_FORCE_INLINE_ Ref<PackedScene> get_packed_scene_world() const { return packed_scene_world; }
	void set_menu_main(MenuMain* p_menu_main);
	void set_packed_scene_world(const Ref<PackedScene>& p_packed_scene_world);

	// ------------------------------------------

public:
	void _on_start_button_pressed();
	void _on_join_button_pressed();
};

#endif // GAME_H
