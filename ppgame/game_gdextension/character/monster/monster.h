#ifndef MONSTER_H
#define MONSTER_H

#include <godot_cpp/classes/character_body2d.hpp>
#include <godot_cpp/classes/navigation_agent2d.hpp>
#include <godot_cpp/classes/wrapped.hpp>
#include <godot_cpp/variant/packed_string_array.hpp>
using namespace godot;

#include "framework/actor.h"

//! 怪物
class Monster : public CharacterBody2D, public Actor {
	GDCLASS(Monster, CharacterBody2D)

public:
	Monster() {}

private:
	NavigationAgent2D* nav_agent = nullptr; //!< 寻路代理

	// ------------------------------------------

private:
	void set_nav_agent(NavigationAgent2D* p_nav_agent);
	NavigationAgent2D* get_nav_agent();

public:
	virtual void _process(double p_delta) override;
	virtual void _physics_process(double p_delta) override;
	virtual PackedStringArray _get_configuration_warnings() const override;

protected:
	static void _bind_methods();
};

#endif // MONSTER_H
