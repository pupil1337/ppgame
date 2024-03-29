#ifndef PLAYER_IDLE_STATE_H
#define PLAYER_IDLE_STATE_H

#include <godot_cpp/classes/wrapped.hpp>

#include "character/player/fsm/motion/ground/player_ground_base_state.h"

class PlayerIdleState : public PlayerGroundBaseState {
	GDCLASS(PlayerIdleState, PlayerGroundBaseState)
};

#endif // PLAYER_IDLE_STATE_H
