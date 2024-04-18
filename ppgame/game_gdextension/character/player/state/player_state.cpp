#include "player_state.h"

#include <godot_cpp/classes/animation_player.hpp>
#include <godot_cpp/variant/string_name.hpp>

#include "character/player/player.h"

void PlayerState::play_animation(const StringName& name /* = String() */, double custom_blend /* = -1 */, double custom_speed /* = 1.0 */, bool from_end /* = false */) {
	if (player) {
		if (AnimationPlayer* animation_player = player->get_animation_player()) {
			animation_player->play(name, custom_blend, custom_speed, from_end);
		}
	}
}
