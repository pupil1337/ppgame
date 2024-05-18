#ifndef WORLD_H
#define WORLD_H

#include "godot_cpp/variant/vector2.hpp"
#include <godot_cpp/classes/node.hpp>
#include <godot_cpp/classes/wrapped.hpp>
#include <godot_cpp/templates/vector.hpp>
#include <godot_cpp/variant/string.hpp>
using namespace godot;

// TODO Delete
#include <GLFW/glfw3.h>
#include <thirdpart/imgui/imgui.h>

class Level;
class Player;

class World : public Node {
	GDCLASS(World, Node)

public:
	static World* get_world(Node* p_inside_node);
	void change_level(const String& p_level, const String& p_player_start);

private:
	void _change_level_internal(const String& p_level, const String& p_player_start);
	void _level_instanced_callback(Node* p_node, const String& p_player_start);

private:
	Level* curr_level = nullptr;
	Player* player = nullptr;

	// TODO Delete
	GLFWwindow* window = nullptr;
	// Our state
	bool show_demo_window = true;
	bool show_another_window = false;
	ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

	// ------------------------------------------

public:
	virtual void _enter_tree() override;
	virtual void _ready() override;
	virtual void _process(double delta) override;
	virtual void _exit_tree() override;

protected:
	void _notification(int p_what);
	static void _bind_methods();
};

#endif // WORLD_H
