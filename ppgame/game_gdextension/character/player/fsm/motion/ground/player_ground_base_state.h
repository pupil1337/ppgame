#ifndef PLAYER_GROUND_BASE_STATE_H
#define PLAYER_GROUND_BASE_STATE_H

#include <godot_cpp/classes/wrapped.hpp>
using namespace godot;

#include "fsm/state.h"

class PlayerGroundBaseState : public State {
	GDCLASS(PlayerGroundBaseState, State)
};

#endif // PLAYER_GROUND_BASE_STATE_H
