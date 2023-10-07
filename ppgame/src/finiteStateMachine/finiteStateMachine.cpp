#include "finiteStateMachine.h"

#include <scene/2d/animated_sprite_2d.h>
#include "state.h"

void FiniteStateMachine::_notification(int p_notification) {
	switch (p_notification) {
		case NOTIFICATION_READY: {
			_ready();
		} break;
	}
}

void FiniteStateMachine::_bind_methods() {
	// curr state
	ClassDB::bind_method(D_METHOD("set_curr_state", "state"), &FiniteStateMachine::set_curr_state);
	ClassDB::bind_method(D_METHOD("get_curr_state"), &FiniteStateMachine::get_curr_state);
	ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "curr_state", PROPERTY_HINT_NODE_TYPE, "State"), "set_curr_state", "get_curr_state");

	// animated sprite
	ClassDB::bind_method(D_METHOD("set_anim_sprite", "anim_sprite"), &FiniteStateMachine::set_anim_sprite);
	ClassDB::bind_method(D_METHOD("get_anim_sprite"), &FiniteStateMachine::get_anim_sprite);
	ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "animated_sprite", PROPERTY_HINT_NODE_TYPE, "AnimatedSprite2D"), "set_anim_sprite", "get_anim_sprite");
}

void FiniteStateMachine::_ready() {
	_add_state_nodes(this);
}

void FiniteStateMachine::_add_state_nodes(Node* node) {
	for (int i = 0; i < node->get_child_count(true); ++i) {
		Node* child = node->get_child(i, true);
		if (State* state = cast_to<State>(child)) {
			ERR_FAIL_COND_EDMSG(states.has(child->get_class_name()), String(node->get_name()) + " has two/more " + String(child->get_class_name()));
			state->fsm = this;
			state->anim_sprite = anim_sprite;
			states[child->get_class_name()] = state;
		} else {
			_add_state_nodes(child);
		}
	}
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

void FiniteStateMachine::set_anim_sprite(AnimatedSprite2D *p_animSprite) {
	ERR_MAIN_THREAD_GUARD;
	anim_sprite = p_animSprite;
}

AnimatedSprite2D* FiniteStateMachine::get_anim_sprite() const {
	ERR_READ_THREAD_GUARD_V(nullptr)
	return anim_sprite;
}
