#ifndef PLAYER_H
#define PLAYER_H

#include <godot_cpp/classes/character_body2d.hpp>

namespace godot {

class Player : public CharacterBody2D {
	GDCLASS(Player, CharacterBody2D)

protected:
	static void _bind_methods();
	
public:
	Player();
	~Player();

private:
	int testA = 1;
};

}

#endif // PLAYER_H