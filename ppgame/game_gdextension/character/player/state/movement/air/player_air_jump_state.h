#ifndef PLAYER_AIR_JUMP_STATE_H
#define PLAYER_AIR_JUMP_STATE_H

#include <godot_cpp/classes/wrapped.hpp>
#include <godot_cpp/variant/string_name.hpp>
using namespace godot;

#include "character/player/state/movement/air/player_air_state.h"

//! 玩家跳跃状态
class PlayerAirJumpState : public PlayerAirState {
	GDCLASS(PlayerAirJumpState, PlayerAirState)

public:
	virtual void enter() override;
	virtual StringName on_process(double delta) override;
	virtual void on_physics_process(double delta) override;
	virtual void exit() override;

public:
	PlayerAirJumpState() {}

private:
	bool desire_jump = false;

	// ------------------------------------------

protected:
	static void _bind_methods() {}
};

#endif // PLAYER_AIR_JUMP_STATE_H
