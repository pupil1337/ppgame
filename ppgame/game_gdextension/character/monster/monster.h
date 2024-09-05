#ifndef MONSTER_H
#define MONSTER_H

#include <godot_cpp/classes/navigation_agent2d.hpp>
#include <godot_cpp/classes/wrapped.hpp>
using namespace godot;

#include "character/character.h"

//! 怪物
class Monster : public Character {
	GDCLASS(Monster, Character)

public:
	NavigationAgent2D* get_nav_agent();

public:
	Monster() {}

	// ------------------------------------------

public:
	virtual void _process(double p_delta) override;
	virtual void _physics_process(double p_delta) override;

protected:
	static void _bind_methods() {}
};

#endif // MONSTER_H
