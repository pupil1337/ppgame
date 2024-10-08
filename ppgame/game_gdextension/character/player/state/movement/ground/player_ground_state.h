#ifndef PLAYER_GROUND_STATE_H
#define PLAYER_GROUND_STATE_H

#include <godot_cpp/classes/wrapped.hpp>
#include <godot_cpp/variant/string_name.hpp>
using namespace godot;

#include "character/player/state/player_state.h"

//! 玩家地面状态基类
class PlayerGroundState : public PlayerState {
	GDCLASS(PlayerGroundState, PlayerState)

public:
	virtual StringName on_process(double delta) override;

public:
	PlayerGroundState() {}

	// ------------------------------------------

protected:
	static void _bind_methods() {}
};

#endif // PLAYER_GROUND_STATE_H
