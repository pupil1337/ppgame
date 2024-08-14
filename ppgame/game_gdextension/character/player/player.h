#ifndef PLAYER_H
#define PLAYER_H

#include <godot_cpp/classes/animation_player.hpp>
#include <godot_cpp/classes/camera2d.hpp>
#include <godot_cpp/classes/character_body2d.hpp>
#include <godot_cpp/classes/sprite2d.hpp>
#include <godot_cpp/classes/wrapped.hpp>
using namespace godot;

#include "framework/actor.h"

//! 角色
class Player : public CharacterBody2D, public Actor {
	GDCLASS(Player, CharacterBody2D)

public:
	//! 获取角色精灵
	Sprite2D* get_sprite();
	//! 获取角色动画播放器
	AnimationPlayer* get_animation_player();
	//! 获取角色摄像机
	Camera2D* get_camera();

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
	static void _bind_methods(){};
};

#endif // PLAYER_H
