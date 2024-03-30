#ifndef PLAYER_IDLE_STATE_H
#define PLAYER_IDLE_STATE_H

#include <godot_cpp/classes/input_event.hpp>
#include <godot_cpp/classes/ref.hpp>
#include <godot_cpp/classes/wrapped.hpp>
#include <godot_cpp/variant/string_name.hpp>
using namespace godot;

#include "character/player/fsm/motion/ground/player_ground_base_state.h"

class PlayerIdleState : public PlayerGroundBaseState {
	GDCLASS(PlayerIdleState, PlayerGroundBaseState)

	virtual void enter() override {}
	virtual StringName on_input(const Ref<InputEvent>& p_event) override { return StringName(); }
	virtual StringName on_process(double delta) override { return StringName(); }
	virtual StringName on_physics_process(double delta) override { return StringName(); }
	virtual void exit() override {}
};

#endif // PLAYER_IDLE_STATE_H
