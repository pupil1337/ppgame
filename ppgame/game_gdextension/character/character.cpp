#include "character.h"

#include <cstdint>
#include <godot_cpp/classes/animation_player.hpp>
#include <godot_cpp/classes/collision_shape2d.hpp>
#include <godot_cpp/classes/sprite2d.hpp>
#include <godot_cpp/variant/packed_string_array.hpp>

#include "character_movement_component.h"
#include "framework/actor.h"

void Character::face_to_input(int8_t p_input_sign_x) {
	if (Sprite2D* sprite = get_sprite()) {
		sprite->set_flip_h(p_input_sign_x < 0);
	}
}

// ----------------------------------------------------------------------------

Sprite2D* Character::get_sprite() const {
	return get_node<Sprite2D>("Sprite2D");
}

AnimationPlayer* Character::get_animation_player() const {
	return get_node<AnimationPlayer>("AnimationPlayer");
}

CollisionShape2D* Character::get_collision_shape() const {
	return get_node<CollisionShape2D>("CollisionShape2D");
}

PackedStringArray Character::_get_configuration_warnings() const {
	PackedStringArray warnings = parent_type::_get_configuration_warnings();

	if (!get_sprite()) {
		warnings.push_back("Not Add Sprite2D");
	}
	if (!get_animation_player()) {
		warnings.push_back("Not Add AnimationPlayer");
	}
	if (!get_collision_shape()) {
		warnings.push_back("Not Add CollisionShape2D");
	}
	if (!Actor::get_child<CharacterMovementComponent>()) {
		warnings.push_back("Not Add CharacterMovementComponent");
	}

	return warnings;
}
