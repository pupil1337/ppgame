#include "player_finite_state_machine_component.h"

#include <godot_cpp/classes/engine.hpp>
#include <godot_cpp/classes/global_constants.hpp>
#include <godot_cpp/classes/object.hpp>
#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/core/defs.hpp>
#include <godot_cpp/core/math.hpp>
#include <godot_cpp/core/object.hpp>
#include <godot_cpp/core/property_info.hpp>
#include <godot_cpp/templates/hash_map.hpp>
#include <godot_cpp/variant/string_name.hpp>
#include <godot_cpp/variant/vector2.hpp>

#include "character/player/player.h"
#include "character/player/player_input_component.h"
#include "character/player/state/movement/player_movement_finite_state_machine_component.h"
#include "character/player/state/player_state.h"
#include "character/player/state/player_state_condition.h"
#include "character/player/state/weapon/player_weapon_finite_state_machine_component.h"
#include "fsm/finite_state_machine_component.h"
#include "fsm/state.h"

void PlayerFiniteStateMachineComponent::_ready() {
	parent_type::_ready();

	if (!Engine::get_singleton()->is_editor_hint()) {
		if (actor) {
			player = static_cast<Player*>(actor);
			player_input_component = actor->get_component<PlayerInputComponent>();
		}

		if (player_movement_fsm) {
			for (HashMap<StringName, State*>::Iterator it = player_movement_fsm->states.begin(); it != player_movement_fsm->states.end(); ++it) {
				if (PlayerState* player_state = Object::cast_to<PlayerState>(it->value)) {
					player_state->player = player;
					player_state->condition = &condition;
				}
			}
		}

		if (player_weapon_fsm) {
			for (HashMap<StringName, State*>::Iterator it = player_weapon_fsm->states.begin(); it != player_movement_fsm->states.end(); ++it) {
				if (PlayerState* player_state = Object::cast_to<PlayerState>(it->value)) {
					player_state->player = player;
					player_state->condition = &condition;
				}
			}
		}

		_update_logic_condition();
		_update_physics_condition();
	}
}

/*!
 * 先更新逻辑条件, 再更新逻辑帧
 */
void PlayerFiniteStateMachineComponent::_process(double p_delta) {
	parent_type::_process(p_delta);

	if (!Engine::get_singleton()->is_editor_hint()) {
		if (player_movement_fsm && player_weapon_fsm) {
			_update_logic_condition();
			player_movement_fsm->on_process(p_delta);
			player_weapon_fsm->on_process(p_delta);
		}
	}
}

/*!
 * 先更新物理帧, 再更新物理条件
 */
void PlayerFiniteStateMachineComponent::_physics_process(double p_delta) {
	parent_type::_physics_process(p_delta);

	if (!Engine::get_singleton()->is_editor_hint()) {
		if (player_movement_fsm && player_weapon_fsm) {
			player_movement_fsm->on_physics_process(p_delta);
			player_weapon_fsm->on_physics_process(p_delta);
			_update_physics_condition();
		}
	}
}

void PlayerFiniteStateMachineComponent::_update_logic_condition() {
	if (player && player_input_component) {
		condition.input_sign_x = player_input_component->get_sign_x();
		condition.input_sign_y = player_input_component->get_sign_y();
		condition.just_pressed_jump = player_input_component->get_just_pressed_jump();
		condition.just_pressed_attack = player_input_component->get_just_pressed_attack();
	}
}

void PlayerFiniteStateMachineComponent::_update_physics_condition() {
	if (player && player_input_component) {
		condition.on_ground = player->is_on_floor();
		condition.can_jump = player->is_on_floor() /* || other  */;
		condition.velocity = player->get_velocity();
	}
}

// ----------------------------------------------------------------------------

void PlayerFiniteStateMachineComponent::set_player_movement_fsm(PlayerMovementFiniteStateMachineComponent* p_player_movement_fsm) {
	player_movement_fsm = p_player_movement_fsm;
}

void PlayerFiniteStateMachineComponent::set_player_weapon_fsm(PlayerWeaponFiniteStateMachineComponent* p_player_weapon_fsm) {
	player_weapon_fsm = p_player_weapon_fsm;
}

PlayerMovementFiniteStateMachineComponent* PlayerFiniteStateMachineComponent::get_player_movement_fsm() {
	return player_movement_fsm;
}

PlayerWeaponFiniteStateMachineComponent* PlayerFiniteStateMachineComponent::get_player_weapon_fsm() {
	return player_weapon_fsm;
}

void PlayerFiniteStateMachineComponent::_bind_methods() {
	// player_movement_fsm
	ClassDB::bind_method(D_METHOD(_STR(set_player_movement_fsm), _STR(player_movement_fsm)), &self_type::set_player_movement_fsm);
	ClassDB::bind_method(D_METHOD(_STR(get_player_movement_fsm)), &self_type::get_player_movement_fsm);
	ADD_PROPERTY(PropertyInfo(Variant::OBJECT, _STR(player_movement_fsm), PROPERTY_HINT_NODE_TYPE, "PlayerMovementFiniteStateMachineComponent"), _STR(set_player_movement_fsm), _STR(get_player_movement_fsm));

	// player_weapon_fsm
	ClassDB::bind_method(D_METHOD(_STR(set_player_weapon_fsm), _STR(player_weapon_fsm)), &self_type::set_player_weapon_fsm);
	ClassDB::bind_method(D_METHOD(_STR(get_player_weapon_fsm)), &self_type::get_player_weapon_fsm);
	ADD_PROPERTY(PropertyInfo(Variant::OBJECT, _STR(player_weapon_fsm), PROPERTY_HINT_NODE_TYPE, "PlayerWeaponFiniteStateMachineComponent"), _STR(set_player_weapon_fsm), _STR(get_player_weapon_fsm));
}
