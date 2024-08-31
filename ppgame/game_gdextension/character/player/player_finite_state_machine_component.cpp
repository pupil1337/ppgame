#include "player_finite_state_machine_component.h"

#include <godot_cpp/classes/engine.hpp>
#include <godot_cpp/classes/object.hpp>
#include <godot_cpp/core/math.hpp>
#include <godot_cpp/templates/hash_map.hpp>
#include <godot_cpp/variant/callable_method_pointer.hpp>
#include <godot_cpp/variant/packed_string_array.hpp>

#include "character/player/player.h"
#include "character/player/player_input_component.h"
#include "character/player/state/player_fsm_input_types.h"
#include "character/player/state/player_state.h"
#include "fsm/state.h"
#include "state/player_finite_state_machine_base_component.h"

void PlayerFiniteStateMachineComponent::_ready() {
	parent_type::_ready();

	if (!Engine::get_singleton()->is_editor_hint()) {
		player = static_cast<Player*>(actor);
		if (player) {
			player_input_component = actor->get_component<PlayerInputComponent>();

			if ((animation_player = player->get_animation_player())) {
				animation_player->connect("animation_finished", callable_mp(this, &self_type::_animation_finished));
			}

			for (int i = 0; i < player_fsms.size(); ++i) {
				if (player_fsms[i]) {
					player_fsms[i]->condition = &condition;
					for (HashMap<StringName, State*>::Iterator it = player_fsms[i]->states.begin(); it != player_fsms[i]->states.end(); ++it) {
						if (PlayerState* player_state = Object::cast_to<PlayerState>(it->value)) {
							player_state->player = player;
							player_state->animation_player = animation_player;
							player_state->player_fsm_component = this;
							player_state->condition = &condition;
						}
					}
				}
			}
		}

		_update_logic_condition();
		_update_physics_condition();
	}
}

void PlayerFiniteStateMachineComponent::_notification(int p_what) {
	if (!Engine::get_singleton()->is_editor_hint()) {
		switch (p_what) {
			case NOTIFICATION_PREDELETE: {
				if (animation_player) {
					animation_player->disconnect("animation_finished", callable_mp(this, &self_type::_animation_finished));
				}
			} break;
		}
	}
}

/*!
 * 先更新逻辑条件, 再更新逻辑帧
 */
void PlayerFiniteStateMachineComponent::_process(double p_delta) {
	parent_type::_process(p_delta);

	if (!Engine::get_singleton()->is_editor_hint()) {
		_update_logic_condition();
		for (int i = 0; i < player_fsms.size(); ++i) {
			if (player_fsms[i]) {
				player_fsms[i]->on_process(p_delta);
			}
		}
	}
}

/*!
 * 先更新物理帧, 再更新物理条件
 */
void PlayerFiniteStateMachineComponent::_physics_process(double p_delta) {
	parent_type::_physics_process(p_delta);

	if (!Engine::get_singleton()->is_editor_hint()) {
		for (int i = 0; i < player_fsms.size(); ++i) {
			if (player_fsms[i]) {
				player_fsms[i]->on_physics_process(p_delta);
			}
		}
		_update_physics_condition();
	}
}

void PlayerFiniteStateMachineComponent::on_input(PlayerFSMInput p_fsm_input, const Variant& p_variant) {
	for (int i = 0; i < player_fsms.size(); ++i) {
		if (player_fsms[i]) {
			player_fsms[i]->on_input((int)p_fsm_input, p_variant);
		}
	}

	_update_logic_condition();
	_update_physics_condition();
}

void PlayerFiniteStateMachineComponent::_update_logic_condition() {
	if (player_input_component) {
		condition.input_sign_x = player_input_component->get_sign_x();
		condition.input_sign_y = player_input_component->get_sign_y();
		condition.just_pressed_jump = player_input_component->get_just_pressed_jump();
		condition.just_pressed_attack = player_input_component->get_just_pressed_attack();
	}
}

void PlayerFiniteStateMachineComponent::_update_physics_condition() {
	if (player) {
		condition.on_ground = player->is_on_floor();
		condition.can_jump = player->is_on_floor();
		condition.velocity = player->get_velocity();
	}
}

void PlayerFiniteStateMachineComponent::condition_add_movement_none_state(int p_count) {
	condition.movement_none_state = Math::max(0, condition.movement_none_state + p_count);
}

void PlayerFiniteStateMachineComponent::condition_add_weapon_none_state(int p_count) {
	condition.weapon_none_state = Math::max(0, condition.weapon_none_state + p_count);
}

void PlayerFiniteStateMachineComponent::condition_add_ban_movement_enter_anim(int p_count) {
	condition.ban_movement_enter_anim = Math::max(0, condition.ban_movement_enter_anim + p_count);
}

void PlayerFiniteStateMachineComponent::condition_add_ban_movement_input(int p_count) {
	condition.ban_movement_input = Math::max(0, condition.ban_movement_input + p_count);
}

void PlayerFiniteStateMachineComponent::_animation_finished(const StringName& p_anim_name) {
	for (int i = 0; i < player_fsms.size(); ++i) {
		if (player_fsms[i]) {
			player_fsms[i]->on_input((int)PlayerFSMInput::Animation_Finished, p_anim_name);
		}
	}
}

// ----------------------------------------------------------------------------

void PlayerFiniteStateMachineComponent::_bind_methods() {
}

PackedStringArray PlayerFiniteStateMachineComponent::_get_configuration_warnings() const {
	PackedStringArray warnings = parent_type::_get_configuration_warnings();

	return warnings;
}
