#ifndef PLAYER_MOVEMENT_NONE_STATE_H
#define PLAYER_MOVEMENT_NONE_STATE_H

#include <godot_cpp/classes/wrapped.hpp>
#include <godot_cpp/variant/string_name.hpp>
using namespace godot;

#include "character/player/state/player_state.h"

class PlayerMovementNoneState : public PlayerState {
	GDCLASS(PlayerMovementNoneState, PlayerState)

public:
	virtual void enter() override;
	virtual StringName on_process(double delta) override { return StringName(); }
	virtual void on_physics_process(double delta) override {}
	virtual void exit() override {}

public:
	PlayerMovementNoneState() {}

	// ------------------------------------------

protected:
	static void _bind_methods() {}
};

#endif // PLAYER_MOVEMENT_NONE_STATE_H
