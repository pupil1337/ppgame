#include "player_finite_state_machine_component.h"

#include <godot_cpp/classes/object.hpp>
#include <godot_cpp/templates/hash_map.hpp>
#include <godot_cpp/variant/string_name.hpp>

#include "character/player/player.h"
#include "character/player/player_input_component.h"
#include "character/player/state/ground/player_ground_idle_state.h"
#include "character/player/state/player_state.h"
#include "character/player/state/player_state_condition.h"
#include "fsm/finite_state_machine_component.h"
#include "fsm/state.h"
#include "godot_cpp/core/math.hpp"
#include "godot_cpp/variant/vector2.hpp"

void PlayerFiniteStateMachineComponent::_ready() {
	start_state_name = PlayerGroundIdleState::get_class_static();

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
}

void PlayerFiniteStateMachineComponent::_process(double p_delta) {
	if (player && player_input_component) {
		Vector2 input_motion = player_input_component->get_motion();
		condition.input_sign_x = Math::sign(player_input_component->get_motion().x);
		condition.juest_pressed_jump = player_input_component->get_just_pressed_jump();
		condition.on_ground = player->is_on_floor();
		condition.can_jump = player->is_on_floor();
		condition.velocity = player->get_velocity();

		FiniteStateMachineComponent::_process(p_delta);
	}
}
