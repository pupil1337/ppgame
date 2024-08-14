#ifndef PLAYER_STATE_H
#define PLAYER_STATE_H

#include <godot_cpp/classes/wrapped.hpp>
#include <godot_cpp/variant/string.hpp>
#include <godot_cpp/variant/string_name.hpp>
#include <godot_cpp/variant/vector2.hpp>
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
	Player* player = nullptr; //!< 角色
	const PlayerStateCondition* condition = nullptr; //!< 状态条件

protected:
	//! 播放动画
	/*!
	 * \param p_name 动画名
	 * \param p_custom_blend 自定义混合时间
	 * \param p_custom_speed 自定义播放速度
	 * \param p_from_end 是否倒着播放
	 */
	void play_animation(const StringName& p_name = String(), double p_custom_blend = -1, double p_custom_speed = 1.0, bool p_from_end = false);

public:
	PlayerState() {}

	// ------------------------------------------

protected:
	static void _bind_methods() {}
};

#endif // PLAYER_STATE_H
