#ifndef PLAYER_AIR_BASE_STATE_H
#define PLAYER_AIR_BASE_STATE_H

#include <godot_cpp/classes/wrapped.hpp>
using namespace godot;

#include "fsm/state.h"

class PlayerAirBaseState : public State {
	GDCLASS(PlayerAirBaseState, State)
};

#endif // PLAYER_AIR_BASE_STATE_H
