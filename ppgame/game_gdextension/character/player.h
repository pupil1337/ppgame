#ifndef PLAYER_H
#define PLAYER_H

#include <godot_cpp/classes/character_body2d.hpp>
using namespace godot;

namespace godot {
class AnimatedSprite2D;
}

class Player : public CharacterBody2D {
	GDCLASS(Player, CharacterBody2D)

public:
	AnimatedSprite2D* animated_sprite2d = nullptr;
	virtual void _ready() override;

protected:
	static void _bind_methods();
};

#endif // PLAYER_H
