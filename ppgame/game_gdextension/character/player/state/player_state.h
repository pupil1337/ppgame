#ifndef PLAYER_STATE_H
#define PLAYER_STATE_H

#include <godot_cpp/classes/wrapped.hpp>
#include <godot_cpp/variant/vector2.hpp>
using namespace godot;

#include "fsm/state.h"

class PlayerFiniteStateMachineComponent;
class Player;

struct PlayerStateCondition;

class PlayerState : public State {
	GDCLASS(PlayerState, State)
	typedef State super;

	friend PlayerFiniteStateMachineComponent;

protected:
	Player* player = nullptr;
	const PlayerStateCondition* condition = nullptr;

	// ------------------------------------------

protected:
	static void _bind_methods() {}
};

#endif // PLAYER_STATE_H
