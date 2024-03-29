#ifndef PLAYER_RUN_STATE_H
#define PLAYER_RUN_STATE_H

#include <godot_cpp/classes/wrapped.hpp>

#include "character/player/fsm/motion/ground/player_ground_base_state.h"

class PlayerRunState : public PlayerGroundBaseState {
	GDCLASS(PlayerRunState, PlayerGroundBaseState)
};

#endif // PLAYER_RUN_STATE_H
