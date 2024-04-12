#ifndef PLAYER_GROUND_IDLE_STATE_H
#define PLAYER_GROUND_IDLE_STATE_H

#include <godot_cpp/classes/wrapped.hpp>
#include <godot_cpp/variant/string_name.hpp>
using namespace godot;

#include "character/player/state/ground/player_ground_state.h"

class PlayerGroundIdleState : public PlayerGroundState {
	GDCLASS(PlayerGroundIdleState, PlayerGroundState)
	typedef PlayerGroundState super;

public:
	virtual void enter() override;
	virtual StringName on_process(double delta) override;
	virtual void on_physics_process(double delta) override;
	virtual void exit() override;

	// ------------------------------------------

protected:
	static void _bind_methods() {}
};

#endif // PLAYER_GROUND_IDLE_STATE_H
