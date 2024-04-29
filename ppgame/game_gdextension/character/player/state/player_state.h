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

class PlayerState : public State {
	GDCLASS(PlayerState, State)

	friend PlayerFiniteStateMachineComponent;

protected:
	Player* player = nullptr;
	const PlayerStateCondition* condition = nullptr;

protected:
	void play_animation(const StringName& name = String(), double custom_blend = -1, double custom_speed = 1.0, bool from_end = false);

	// ------------------------------------------

protected:
	static void _bind_methods() {}
};

#endif // PLAYER_STATE_H
