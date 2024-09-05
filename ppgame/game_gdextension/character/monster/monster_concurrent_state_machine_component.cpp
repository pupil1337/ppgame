#include "monster_concurrent_state_machine_component.h"

#include <godot_cpp/classes/object.hpp>
#include <godot_cpp/templates/vector.hpp>

#include "character/character_movement_component.h"
#include "character/monster/monster.h"
#include "character/monster/state/monster_state_condition.h"
#include "fsm/state.h"
#include "fsm/state_condition.h"
#include "state/monster_state.h"

StateCondition* MonsterConcurrentStateMachineComponent::_new_condition() {
	return new MonsterStateCondition();
}

void MonsterConcurrentStateMachineComponent::_init_those_state_mem(const Vector<State*> p_states) {
	if (Monster* monster = static_cast<Monster*>(actor)) {
		for (int i = 0; i != p_states.size(); ++i) {
			if (MonsterState* monster_state = Object::cast_to<MonsterState>(p_states[i])) {
				monster_state->monster = monster;
				monster_state->character_movement_component = monster->get_component<CharacterMovementComponent>();
				monster_state->nav_agent = monster->get_nav_agent();
				monster_state->condition = static_cast<const MonsterStateCondition*>(condition);
			}
		}
	}
}

void MonsterConcurrentStateMachineComponent::_update_logic_condition() {
}

void MonsterConcurrentStateMachineComponent::_update_physics_condition() {
	if (Monster* monster = static_cast<Monster*>(actor)) {
		static_cast<MonsterStateCondition*>(condition)->velocity = monster->get_velocity();
		static_cast<MonsterStateCondition*>(condition)->global_position = monster->get_global_position();
	}
}
