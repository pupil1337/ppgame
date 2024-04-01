#ifndef PLAYER_FALL_STATE_H
#define PLAYER_FALL_STATE_H

#include <godot_cpp/classes/input_event.hpp>
#include <godot_cpp/classes/ref.hpp>
#include <godot_cpp/classes/wrapped.hpp>
using namespace godot;

#include "character/player/fsm/motion/air/player_air_base_state.h"

namespace godot {
class StringName;
}

class PlayerFallState : public PlayerAirBaseState {
	GDCLASS(PlayerFallState, PlayerAirBaseState)

	virtual void enter() override {}
	virtual StringName on_input(const Ref<InputEvent>& p_event) override { return StringName(); }
	virtual StringName on_process(double delta) override { return StringName(); }
	virtual StringName on_physics_process(double delta) override { return StringName(); }
	virtual void exit() override {}

	// ------------------------------------------
};

#endif // PLAYER_FALL_STATE_H
