#ifndef PLAYER_STATE_H
#define PLAYER_STATE_H

#include <godot_cpp/classes/animation_player.hpp>
#include <godot_cpp/classes/area2d.hpp>
#include <godot_cpp/classes/collision_shape2d.hpp>
#include <godot_cpp/classes/wrapped.hpp>
#include <godot_cpp/variant/string_name.hpp>
using namespace godot;

#include "fsm/state.h"

class PlayerConcurrentStateMachineComponent;
class Player;
struct PlayerStateCondition;

//! 玩家状态基类
class PlayerState : public State {
	GDCLASS(PlayerState, State)

	friend PlayerConcurrentStateMachineComponent;

protected:
	Player* player = nullptr; //!< 玩家
	AnimationPlayer* animation_player = nullptr; //!< 动画播放器
	Area2D* player_melee_attack_area = nullptr; //!< 近战攻击区域
	CollisionShape2D* player_melee_attack_shape = nullptr; //!< 近战攻击形状
	PlayerConcurrentStateMachineComponent* player_csm_component = nullptr; //!< 并发状态机组件
	const PlayerStateCondition* condition = nullptr; //!< 状态条件

public:
	PlayerState() {}

	// ------------------------------------------

protected:
	static void _bind_methods() {}
};

#endif // PLAYER_STATE_H
