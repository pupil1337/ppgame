#ifndef PLAYER_GROUND_RUN_STATE_H
#define PLAYER_GROUND_RUN_STATE_H

#include <godot_cpp/classes/wrapped.hpp>
#include <godot_cpp/variant/string_name.hpp>
using namespace godot;

#include "character/player/state/movement/ground/player_ground_state.h"

//! 玩家奔跑状态
class PlayerGroundRunState : public PlayerGroundState {
	GDCLASS(PlayerGroundRunState, PlayerGroundState)

public:
	virtual void enter() override;
	virtual StringName on_process(double delta) override;
	virtual void on_physics_process(double delta) override;
	virtual void exit() override;

public:
	PlayerGroundRunState() {}

	// ------------------------------------------

protected:
	static void _bind_methods() {}
};

#endif // PLAYER_GROUND_RUN_STATE_H
