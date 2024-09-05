#include "player_concurrent_state_machine_component.h"

#include <godot_cpp/classes/animation_player.hpp>
#include <godot_cpp/classes/area2d.hpp>
#include <godot_cpp/classes/collision_shape2d.hpp>
#include <godot_cpp/classes/engine.hpp>
#include <godot_cpp/classes/node2d.hpp>
#include <godot_cpp/classes/object.hpp>
#include <godot_cpp/core/math.hpp>
#include <godot_cpp/templates/vector.hpp>
#include <godot_cpp/variant/callable_method_pointer.hpp>
#include <godot_cpp/variant/string_name.hpp>

#include "character/player/player.h"
#include "character/player/state/player_fsm_input_types.h"
#include "character/player/state/player_state.h"
#include "fsm/finite_state_machine_component.h"
#include "fsm/state_condition.h"
#include "player_input_component.h"
#include "state/player_state_condition.h"

StateCondition* PlayerConcurrentStateMachineComponent::_new_condition() {
	return new PlayerStateCondition();
}

void PlayerConcurrentStateMachineComponent::_init_those_state_mem(const Vector<State*> p_states) {
	if (Player* player = static_cast<Player*>(actor)) {
		AnimationPlayer* animation_player = player->get_animation_player();
		Area2D* player_melee_attack_area = player->get_melee_attack_area();
		CollisionShape2D* player_melee_attack_shape = player->get_melee_attack_shape();
		for (int i = 0; i < p_states.size(); ++i) {
			if (PlayerState* player_state = Object::cast_to<PlayerState>(p_states[i])) {
				player_state->player = player;
				player_state->animation_player = animation_player;
				player_state->player_melee_attack_area = player_melee_attack_area;
				player_state->player_melee_attack_shape = player_melee_attack_shape;
				player_state->player_csm_component = this;
				player_state->condition = static_cast<const PlayerStateCondition*>(condition);
			}
		}
	}
}

void PlayerConcurrentStateMachineComponent::_ready() {
	parent_type::_ready();

	if (!Engine::get_singleton()->is_editor_hint()) {
		if (Player* player = static_cast<Player*>(actor)) {
			if (AnimationPlayer* animation_player = player->get_animation_player()) {
				animation_player->connect("animation_finished", callable_mp(this, &self_type::_animation_finished));
			}
			if (Area2D* player_melee_attack_area = player->get_melee_attack_area()) {
				player_melee_attack_area->connect("body_entered", callable_mp(this, &self_type ::_body_enter_melee_attack));
				player_melee_attack_area->connect("body_exited", callable_mp(this, &self_type ::_body_exit_melee_attack));
			}
		}
	}
}

void PlayerConcurrentStateMachineComponent::_update_logic_condition() {
	if (actor) {
		if (PlayerInputComponent* player_input_component = actor->get_component<PlayerInputComponent>()) {
			static_cast<PlayerStateCondition*>(condition)->input_sign_x = player_input_component->get_sign_x();
			static_cast<PlayerStateCondition*>(condition)->input_sign_y = player_input_component->get_sign_y();
			static_cast<PlayerStateCondition*>(condition)->just_pressed_jump = player_input_component->get_just_pressed_jump();
			static_cast<PlayerStateCondition*>(condition)->just_pressed_attack = player_input_component->get_just_pressed_attack();
		}
	}
}

void PlayerConcurrentStateMachineComponent::_update_physics_condition() {
	if (actor) {
		if (Player* player = static_cast<Player*>(actor)) {
			static_cast<PlayerStateCondition*>(condition)->on_ground = player->is_on_floor();
			static_cast<PlayerStateCondition*>(condition)->can_jump = player->is_on_floor();
			static_cast<PlayerStateCondition*>(condition)->velocity = player->get_velocity();
		}
	}
}

void PlayerConcurrentStateMachineComponent::condition_add_movement_none_state(int p_count) {
	static_cast<PlayerStateCondition*>(condition)->movement_none_state = Math::max(0, static_cast<PlayerStateCondition*>(condition)->movement_none_state + p_count);
}

void PlayerConcurrentStateMachineComponent::condition_add_weapon_none_state(int p_count) {
	static_cast<PlayerStateCondition*>(condition)->weapon_none_state = Math::max(0, static_cast<PlayerStateCondition*>(condition)->weapon_none_state + p_count);
}

void PlayerConcurrentStateMachineComponent::condition_add_ban_movement_enter_anim(int p_count) {
	static_cast<PlayerStateCondition*>(condition)->ban_movement_enter_anim = Math::max(0, static_cast<PlayerStateCondition*>(condition)->ban_movement_enter_anim + p_count);
}

void PlayerConcurrentStateMachineComponent::condition_add_ban_movement_input(int p_count) {
	static_cast<PlayerStateCondition*>(condition)->ban_movement_input = Math::max(0, static_cast<PlayerStateCondition*>(condition)->ban_movement_input + p_count);
}

void PlayerConcurrentStateMachineComponent::_animation_finished(const StringName& p_anim_name) {
	for (int i = 0; i < fsms.size(); ++i) {
		if (fsms[i]) {
			fsms[i]->on_input((int)PlayerFSMInput::Animation_Finished, p_anim_name);
		}
	}
}

void PlayerConcurrentStateMachineComponent::_body_enter_melee_attack(Node2D* p_body) {
	if (Player* player = static_cast<Player*>(actor)) {
		if (CollisionShape2D* player_melee_attack_shape = player->get_melee_attack_shape()) {
			player_melee_attack_shape->set_debug_color(Color(1, 0, 0, 0.067));
		}
	}

	for (int i = 0; i < fsms.size(); ++i) {
		if (fsms[i]) {
			fsms[i]->on_input((int)PlayerFSMInput::Body_Enter_Melee_Attack, p_body);
		}
	}
}

void PlayerConcurrentStateMachineComponent::_body_exit_melee_attack(Node2D* p_body) {
	if (Player* player = static_cast<Player*>(actor)) {
		if (CollisionShape2D* player_melee_attack_shape = player->get_melee_attack_shape()) {
			player_melee_attack_shape->set_debug_color(Color(1, 1, 0, 0.067));
		}
	}

	for (int i = 0; i < fsms.size(); ++i) {
		if (fsms[i]) {
			fsms[i]->on_input((int)PlayerFSMInput::Body_Exit_Melee_Attack, p_body);
		}
	}
}
