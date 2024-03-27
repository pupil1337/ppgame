#ifndef PLAYER_JUMP_STATE_H
#define PLAYER_JUMP_STATE_H

#include "character/player/fsm/motion/air/player_air_base_state.h"

class PlayerJumpState : public PlayerAirBaseState {
	GDCLASS(PlayerJumpState, PlayerAirBaseState)
};

#endif // PLAYER_JUMP_STATE_H
