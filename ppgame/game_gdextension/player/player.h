#ifndef PLAYER_H
#define PLAYER_H

#include <godot_cpp/classes/character_body2d.hpp>
using namespace godot;

class Player : public CharacterBody2D {
	GDCLASS(Player, CharacterBody2D)

protected:
	static void _bind_methods();
};

#endif // PLAYER_H
