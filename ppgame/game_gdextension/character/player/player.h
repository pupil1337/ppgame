#ifndef PLAYER_H
#define PLAYER_H

#include <godot_cpp/classes/character_body2d.hpp>
#include <godot_cpp/classes/wrapped.hpp>
using namespace godot;

#include "framework/actor.h"

class Player : public CharacterBody2D, public Actor {
	GDCLASS(Player, CharacterBody2D)

	// ------------------------------------------

public:
	virtual void _ready() override;
	virtual void _process(double delta) override;
	virtual void _physics_process(double delta) override;

protected:
	static void _bind_methods() {}
};

#endif // PLAYER_H
