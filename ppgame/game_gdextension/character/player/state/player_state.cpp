#include "player_state.h"

#include <godot_cpp/classes/animation_player.hpp>
#include <godot_cpp/variant/string_name.hpp>

#include "character/player/player.h"

void PlayerState::play_animation(const StringName& p_name /* = String() */, double p_custom_blend /* = -1 */, double p_custom_speed /* = 1.0 */, bool p_from_end /* = false */) {
	if (player) {
		if (AnimationPlayer* animation_player = player->get_animation_player()) {
			animation_player->play(p_name, p_custom_blend, p_custom_speed, p_from_end);
		}
	}
}
