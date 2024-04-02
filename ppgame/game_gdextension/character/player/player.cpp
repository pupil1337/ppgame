#include "player.h"

#include <godot_cpp/classes/input_event.hpp>
#include <godot_cpp/classes/ref.hpp>

void Player::_ready() {
	initialize_components();
}

void Player::_bind_methods() {
}
