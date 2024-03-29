#ifndef PLAYER_FALL_STATE_H
#define PLAYER_FALL_STATE_H

#include <godot_cpp/classes/wrapped.hpp>

#include "character/player/fsm/motion/air/player_air_base_state.h"

class PlayerFallState : public PlayerAirBaseState {
	GDCLASS(PlayerFallState, PlayerAirBaseState)
};

#endif // PLAYER_FALL_STATE_H
