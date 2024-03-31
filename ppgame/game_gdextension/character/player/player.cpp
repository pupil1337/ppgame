#include "player.h"

#include <godot_cpp/classes/engine.hpp>
#include <godot_cpp/classes/input_event.hpp>
#include <godot_cpp/classes/ref.hpp>

#include "character/player/fsm/player_finite_state_machine_component.h"

void Player::_ready() {
	if (!Engine::get_singleton()->is_editor_hint()) {
		initialize_components();
	}
}

void Player::_unhandled_key_input(const Ref<InputEvent>& p_event) {
	if (PlayerFiniteStateMachineComponent* fsm = get_component<PlayerFiniteStateMachineComponent>()) {
		fsm->on_input(p_event);
	}
}

void Player::_bind_methods() {
}
