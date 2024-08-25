#ifndef PLAYER_STATE_H
#define PLAYER_STATE_H

#include <godot_cpp/classes/animation_player.hpp>
#include <godot_cpp/classes/wrapped.hpp>
#include <godot_cpp/variant/string_name.hpp>
using namespace godot;

#include "fsm/state.h"

class PlayerFiniteStateMachineComponent;
class Player;
struct PlayerStateCondition;

//! 角色状态基类
class PlayerState : public State {
	GDCLASS(PlayerState, State)

	friend PlayerFiniteStateMachineComponent;

protected:
	virtual void on_animation_finished(const StringName& p_anim_name) {}

protected:
	Player* player = nullptr; //!< 角色
	AnimationPlayer* animation_player = nullptr; //!< 动画播放器
	PlayerFiniteStateMachineComponent* player_fsm_component = nullptr; //!< 状态机组件
	const PlayerStateCondition* condition = nullptr; //!< 状态条件

public:
	PlayerState() {}

	// ------------------------------------------

protected:
	static void _bind_methods() {}
};

#endif // PLAYER_STATE_H
