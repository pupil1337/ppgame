#ifndef CHARACTER
#define CHARACTER

#include <cstdint>
#include <godot_cpp/classes/animation_player.hpp>
#include <godot_cpp/classes/character_body2d.hpp>
#include <godot_cpp/classes/collision_shape2d.hpp>
#include <godot_cpp/classes/sprite2d.hpp>
#include <godot_cpp/classes/wrapped.hpp>
#include <godot_cpp/variant/packed_string_array.hpp>
using namespace godot;

#include "framework/actor.h"

//! 角色基类
class Character : public CharacterBody2D, public Actor {
	GDCLASS(Character, CharacterBody2D)

public:
	//! 面朝输入
	virtual void face_to_input(int8_t p_input_sign_x);

public:
	//! 获取精灵
	Sprite2D* get_sprite() const;
	//! 获取动画播放器
	AnimationPlayer* get_animation_player() const;
	//! 获取碰撞形状
	CollisionShape2D* get_collision_shape() const;

public:
	Character() :
			Actor(this) {}

	// ------------------------------------------

public:
	virtual PackedStringArray _get_configuration_warnings() const override;

protected:
	static void _bind_methods() {}
};

#endif // CHARACTER
