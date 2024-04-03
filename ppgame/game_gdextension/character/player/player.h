#ifndef PLAYER_H
#define PLAYER_H

#include <cstdint>
#include <godot_cpp/classes/character_body2d.hpp>
#include <godot_cpp/classes/input_event.hpp>
#include <godot_cpp/classes/ref.hpp>
#include <godot_cpp/classes/wrapped.hpp>
using namespace godot;

#include "framework/actor.h"

class Player : public CharacterBody2D, public Actor {
	GDCLASS(Player, CharacterBody2D)

	// ------------------------------------------

public:
	virtual void _ready() override;

	void set_id(uint32_t p_id);
	uint32_t get_id() const;

	uint32_t id = 55;

protected:
	static void _bind_methods();
};

#endif // PLAYER_H
