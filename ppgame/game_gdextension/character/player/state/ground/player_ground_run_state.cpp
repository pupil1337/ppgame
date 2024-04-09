#include "player_ground_run_state.h"

#include "character/player/player.h"
#include "character/player/player_movement_component.h"

#include <godot_cpp/variant/string_name.hpp>

void PlayerGroundRunState::enter() {
}

StringName PlayerGroundRunState::on_physics_process(double delta) {
	if (player) {
		if (PlayerMovementComponent* player_movement_component = player->get_component<PlayerMovementComponent>()) {
		}
	}

	return StringName();
}

void PlayerGroundRunState::exit() {
}
