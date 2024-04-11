#ifndef PLAYER_AIR_JUMP_DASH_STATE_H
#define PLAYER_AIR_JUMP_DASH_STATE_H

#include <godot_cpp/classes/wrapped.hpp>
#include <godot_cpp/variant/string_name.hpp>
using namespace godot;

#include "character/player/state/air/player_air_jump_state.h"

// TODO: 删除PlayerAirJumpDashState例子
class PlayerAirJumpDashState : public PlayerAirJumpState {
	GDCLASS(PlayerAirJumpDashState, PlayerAirJumpState)

public:
	virtual void enter() override;
	virtual StringName on_process(double delta) override;
	virtual void on_physics_process(double delta) override;
	virtual void exit() override;
	// ------------------------------------------

protected:
	static void _bind_methods() {}
};

#endif // PLAYER_AIR_JUMP_DASH_STATE_H
