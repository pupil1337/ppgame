#ifndef PLAYER_H
#define PLAYER_H

#include <godot_cpp/classes/character_body2d.hpp>

using namespace godot;

class Playertest : public CharacterBody2D {
	GDCLASS(Playertest, CharacterBody2D)

protected:
	static void _bind_methods();

public:
	virtual void _ready() override;
};

#endif // PLAYER_H
