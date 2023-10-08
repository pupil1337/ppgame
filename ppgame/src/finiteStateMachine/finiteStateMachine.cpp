#include "finiteStateMachine.h"

#include <scene/2d/animated_sprite_2d.h>
#include "state.h"

void FiniteStateMachine::_bind_methods() {
	// curr state
	ClassDB::bind_method(D_METHOD("set_curr_state", "state"), &FiniteStateMachine::set_curr_state);
	ClassDB::bind_method(D_METHOD("get_curr_state"), &FiniteStateMachine::get_curr_state);
	ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "curr_state", PROPERTY_HINT_NODE_TYPE, "State"), "set_curr_state", "get_curr_state");
}

void FiniteStateMachine::_notification(int p_notification) {
	switch (p_notification) {
		case NOTIFICATION_READY: {
			_add_state_nodes(this);
		} break;
	}
}

void FiniteStateMachine::_add_state_nodes(Node* node) {
	for (int i = 0; i < node->get_child_count(true); ++i) {
		Node* child = node->get_child(i, true);
		if (State* state = Object::cast_to<State>(child)) {
			ERR_FAIL_COND_EDMSG(states.has(child->get_class_name()), String(node->get_name()) + " has two/more " + String(child->get_class_name()));
			state->fsm = this;
			states[child->get_class_name()] = state;
		} else {
			_add_state_nodes(child);
		}
	}
}

void FiniteStateMachine::on_ready() {
	info.owner = get_parent();
	info.anim_sprite = Object::cast_to<AnimatedSprite2D>(info.owner->call("get_anim_sprite"));

	ERR_FAIL_NULL_EDMSG(curr_state, String(get_name()) + " not set start_state_node in editor");
	StringName start_state_name = curr_state->get_class_name();
	curr_state = nullptr;
	_change_state(start_state_name);
}

void FiniteStateMachine::_change_state(const StringName& new_state_name) {
	if (curr_state) {
		curr_state->exit();
	}

	ERR_FAIL_COND_EDMSG(!states.has(new_state_name), String(get_parent()->get_class_name()) + "'fsm->" + get_class_name() + " not has state: " + String(new_state_name));
	curr_state = states.get(new_state_name);
	curr_state->enter();
}

void FiniteStateMachine::on_input(const Ref<InputEvent> &p_event) {
	if (curr_state) {
		String new_state_name = curr_state->on_input(p_event);
		if (!new_state_name.is_empty()) {
			_change_state(new_state_name);
		}
	}
}

void FiniteStateMachine::on_process(float deltaTime) {
	if (curr_state) {
		String new_state_name = curr_state->on_process(deltaTime);
		if (!new_state_name.is_empty()) {
			_change_state(new_state_name);
		}
	}
}


void FiniteStateMachine::on_physics_process(float deltaTime) {
	if (curr_state) {
		String new_state_name = curr_state->on_physics_process(deltaTime);
		if (!new_state_name.is_empty()) {
			_change_state(new_state_name);
		}
	}
}

// setting --------------------------------------------------------------------
void FiniteStateMachine::set_curr_state(State *p_state) {
	ERR_MAIN_THREAD_GUARD;
	curr_state = p_state;
}

State* FiniteStateMachine::get_curr_state() const {
	ERR_READ_THREAD_GUARD_V(nullptr);
	return curr_state;
}

