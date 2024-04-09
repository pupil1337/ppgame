#include "player.h"

#include <godot_cpp/classes/character_body2d.hpp>

void Player::_ready() {
	CharacterBody2D::_ready();
}

void Player::_process(double delta) {
	CharacterBody2D::_process(delta);
}
