#include "player_finite_state_machine_component.h"

#include <godot_cpp/classes/engine.hpp>
#include <godot_cpp/classes/object.hpp>
#include <godot_cpp/core/math.hpp>
#include <godot_cpp/templates/hash_map.hpp>
#include <godot_cpp/variant/string_name.hpp>
#include <godot_cpp/variant/vector2.hpp>

#include "character/player/player.h"
#include "character/player/player_input_component.h"
#include "character/player/state/player_state.h"
#include "character/player/state/player_state_condition.h"
#include "fsm/finite_state_machine_component.h"
#include "fsm/state.h"

void PlayerFiniteStateMachineComponent::_ready() {
	parent_type::_ready();

	if (!Engine::get_singleton()->is_editor_hint()) {
		if (actor) {
			player = static_cast<Player*>(actor);
			player_input_component = actor->get_component<PlayerInputComponent>();
		}

		for (HashMap<StringName, State*>::Iterator it = states.begin(); it != states.end(); ++it) {
			if (PlayerState* player_state = Object::cast_to<PlayerState>(it->value)) {
				player_state->player = player;
				player_state->condition = &condition;
			}
		}

		_update_physics_condition();
	}
}

void PlayerFiniteStateMachineComponent::on_process(double p_delta) {
	_update_logic_condition();
	parent_type::on_process(p_delta);
}

void PlayerFiniteStateMachineComponent::on_physics_process(double p_delta) {
	parent_type::on_physics_process(p_delta);
	_update_physics_condition();
}

void PlayerFiniteStateMachineComponent::_update_logic_condition() {
	if (player && player_input_component) {
		condition.input_sign_x = player_input_component->get_sign_x();
		condition.just_pressed_jump = player_input_component->get_just_pressed_jump();
	}
}

void PlayerFiniteStateMachineComponent::_update_physics_condition() {
	if (player && player_input_component) {
		condition.on_ground = player->is_on_floor();
		condition.can_jump = player->is_on_floor() /* || other  */;
		condition.velocity = player->get_velocity();
	}
}
