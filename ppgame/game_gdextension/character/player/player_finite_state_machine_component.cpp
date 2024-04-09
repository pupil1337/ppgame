#include "player_finite_state_machine_component.h"

#include <godot_cpp/classes/object.hpp>
#include <godot_cpp/templates/hash_map.hpp>
#include <godot_cpp/variant/string_name.hpp>

#include "character/player/player.h"
#include "character/player/player_input_component.h"
#include "character/player/state/player_state.h"
#include "character/player/state/player_state_condition.h"
#include "fsm/finite_state_machine_component.h"
#include "fsm/state.h"

PlayerFiniteStateMachineComponent::PlayerFiniteStateMachineComponent() {
	condition = new PlayerStateCondition();
}

PlayerFiniteStateMachineComponent::~PlayerFiniteStateMachineComponent() {
	delete condition;
}

void PlayerFiniteStateMachineComponent::_ready() {
	FiniteStateMachineComponent::_ready();

	if (actor) {
		player = static_cast<Player*>(actor);
	}

	for (HashMap<StringName, State*>::Iterator it = states.begin(); it != states.end(); ++it) {
		if (PlayerState* player_state = Object::cast_to<PlayerState>(it->value)) {
			player_state->player = player;
			player_state->condition = condition;
		}
	}
}

void PlayerFiniteStateMachineComponent::on_process(double p_delta) {
	if (player) {
		if (PlayerInputComponent* player_input_component = player->get_component<PlayerInputComponent>()) {
			condition->input_motion = player_input_component->get_motion();
			condition->pressed_jump = player_input_component->get_pressed_jump();
			condition->on_ground = player->is_on_floor();
		}
	}
	FiniteStateMachineComponent::on_process(p_delta);
}
