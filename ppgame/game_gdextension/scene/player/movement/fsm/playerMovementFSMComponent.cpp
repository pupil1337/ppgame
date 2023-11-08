#include "playerMovementFSMComponent.h"

#include "scene/player/movement/fsm/playerMovementStateBase.h"
#include "scene/player/player.h"

void PlayerMovementFSMComponent::_bind_methods() {
	// player
	ClassDB::bind_method(D_METHOD(_STR(set_player), _STR(player)), &self_type::set_player);
	ClassDB::bind_method(D_METHOD(_STR(get_player)), &self_type::get_player);
	ADD_PROPERTY(PropertyInfo(Variant::OBJECT, _STR(player), PROPERTY_HINT_NODE_TYPE, "Player"), _STR(set_player), _STR(get_player));
}

void PlayerMovementFSMComponent::set_player(Player* p_player) {
	player = p_player;
}

// ----------------------------------------------------------------------------

void PlayerMovementFSMComponent::pre_owner_ready() {
	FiniteStateMachineComponent::pre_owner_ready();

	ERR_FAIL_COND_EDMSG(!states.has(StringName("PlayerIdleState")), String(get_parent()->get_name()) + "'" + String(get_name()) + " not has state: PlayerIdleState");
	curr_state = states.get(StringName("PlayerIdleState"));
	for (HashMap<StringName, State*>::Iterator it = states.begin(); it != states.end(); ++it) {
		if (PlayerMovementStateBase* state = Object::cast_to<PlayerMovementStateBase>(it->value)) {
			state->fsm = this;
		}
	}
}
