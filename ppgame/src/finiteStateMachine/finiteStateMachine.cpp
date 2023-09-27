#include "finiteStateMachine.h"

#include "state.h"

void FiniteStateMachine::_notification(int p_notification) {
	switch (p_notification) {
		case NOTIFICATION_READY: {
			set_process(true);
			set_physics_process(true);

			_ready();
		} break;

		case NOTIFICATION_PROCESS: {
			_process(get_process_delta_time());
		} break;

		case NOTIFICATION_PHYSICS_PROCESS: {
			_physics_process(get_physics_process_delta_time());
		} break;
	}
}

void FiniteStateMachine::_ready() {
	_initialize_state_nodes(this);
}

void FiniteStateMachine::_initialize_state_nodes(Node* node) {
	if (node == nullptr) {
		print_line("%s node = nullptr", __FUNCTION__);
		return;
	}

	for (int i = 0; i < node->get_child_count(true); ++i) {
		Node* child = node->get_child(i, true);
		if (child->is_class(State::get_class_static())) {
			if (child->is_inside_tree()) {
				states[child->get_name()] = cast_to<State>(get_node(child->get_path()));
			}
		} else {
			_initialize_state_nodes(child);
		}
	}
}

void FiniteStateMachine::_process(float deltaTime)
{

}

void FiniteStateMachine::_physics_process(float deltaTime)
{

}
