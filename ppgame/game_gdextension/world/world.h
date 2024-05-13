#ifndef WORLD_H
#define WORLD_H

#include <godot_cpp/classes/node.hpp>
#include <godot_cpp/classes/wrapped.hpp>
#include <godot_cpp/templates/vector.hpp>
#include <godot_cpp/variant/string.hpp>
using namespace godot;

class Level;
class Player;

class World : public Node {
	GDCLASS(World, Node)

public:
	static World* get_world(Node* p_inside_node);
	void add_level_and_player_tp(Level* p_level, const String& p_player_start);

private:
	void _level_instanced_callback(Node* p_node);
	void _player_instanced_callback(Node* p_node);

private:
	Level* curr_level = nullptr;
	Player* player = nullptr;

	// ------------------------------------------

public:
	virtual void _ready() override;

protected:
	void _notification(int p_what);
	static void _bind_methods() {}
};

#endif // WORLD_H
