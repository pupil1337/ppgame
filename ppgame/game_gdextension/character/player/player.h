#ifndef PLAYER_H
#define PLAYER_H

#include <godot_cpp/classes/animation_player.hpp>
#include <godot_cpp/classes/character_body2d.hpp>
#include <godot_cpp/classes/sprite2d.hpp>
#include <godot_cpp/classes/wrapped.hpp>
using namespace godot;

#include "framework/actor.h"

class Player : public CharacterBody2D, public Actor {
	GDCLASS(Player, CharacterBody2D)
	typedef CharacterBody2D super;

private:
	Sprite2D* sprite = nullptr;
	AnimationPlayer* animation_player = nullptr;

	// ------------------------------------------

public:
	Sprite2D* get_sprite();
	AnimationPlayer* get_animation_player();

private:
	void set_sprite(Sprite2D* p_sprite);
	void set_animation_player(AnimationPlayer* p_animation_player);

public:
	virtual void _ready() override;
	virtual void _process(double delta) override;
	virtual void _physics_process(double delta) override;

protected:
	static void _bind_methods();
};

#endif // PLAYER_H
