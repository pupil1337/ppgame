#include "player_input_component.h"

#include <godot_cpp/classes/input.hpp>
#include <godot_cpp/classes/input_event.hpp>
#include <godot_cpp/classes/ref.hpp>
#include <godot_cpp/variant/vector2.hpp>

#include "character/player/player_movement_component.h"
#include "framework/actor.h"

void PlayerInputComponent::_ready() {
	player_movement_component = actor->get_component<PlayerMovementComponent>();
}

void PlayerInputComponent::_process(double delta) {
	motion = Input::get_singleton()->get_vector("Left", "Right", "Up", "Down");
}

void PlayerInputComponent::_unhandled_input(const Ref<InputEvent>& p_event) {
	if (p_event->is_action("Jump")) {
		// TODO fsm输入而非直接调用movement_component
		if (player_movement_component) {
			if (p_event->is_pressed()) {
				if (!p_event->is_echo()) {
					player_movement_component->jump();
				}
			} else if (p_event->is_released()) {
				player_movement_component->stop_jumping();
			}
		}
	}
}

Vector2 PlayerInputComponent::get_motion() {
	return motion;
}
