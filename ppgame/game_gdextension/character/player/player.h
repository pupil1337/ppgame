#ifndef PLAYER_H
#define PLAYER_H

#include <cstdint>
#include <godot_cpp/classes/area2d.hpp>
#include <godot_cpp/classes/collision_shape2d.hpp>
#include <godot_cpp/classes/wrapped.hpp>
using namespace godot;

#include "character/character.h"

//! 玩家
class Player : public Character {
	GDCLASS(Player, Character)

public:
	virtual void face_to_input(int8_t p_input_sign_x) override;

public:
	//! 获取近战攻击区域
	Area2D* get_melee_attack_area();
	//! 获取近战攻击形状
	CollisionShape2D* get_melee_attack_shape();

public:
	Player() {}

	// ------------------------------------------

public:
	virtual void _enter_tree() override;
	virtual void _ready() override;
	virtual void _process(double delta) override;
	virtual void _physics_process(double delta) override;
	virtual void _exit_tree() override;

protected:
	static void _bind_methods() {};
};

#endif // PLAYER_H
