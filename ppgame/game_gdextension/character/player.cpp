#include "player.h"

#include <godot_cpp/classes/animated_sprite2d.hpp>

void Player::_ready() {
	animated_sprite2d = get_node<AnimatedSprite2D>("AnimatedSprite2D");
}

void Player::_bind_methods() {
}
