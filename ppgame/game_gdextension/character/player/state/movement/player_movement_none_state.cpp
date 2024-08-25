#include "player_movement_none_state.h"

#include "character/player/player.h"

void PlayerMovementNoneState::enter() {
	if (player) {
		player->set_velocity({ 0.0, 0.0 });
		player->move_and_slide();
	}
}
