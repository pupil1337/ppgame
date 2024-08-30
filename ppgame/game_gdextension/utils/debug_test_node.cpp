#include "debug_test_node.h"

#include <godot_cpp/variant/packed_string_array.hpp>
#include <godot_cpp/variant/utility_functions.hpp>

void DebugTestNode::_process(double p_delta) {
	parent_type::_process(p_delta);
}

void DebugTestNode::_physics_process(double p_delta) {
	parent_type::_physics_process(p_delta);
}

void DebugTestNode::_enter_tree() {
	parent_type::_enter_tree();
}

void DebugTestNode::_exit_tree() {
	parent_type::_exit_tree();
}

void DebugTestNode::_ready() {
	parent_type::_ready();
}

PackedStringArray DebugTestNode::_get_configuration_warnings() const {
	return parent_type::_get_configuration_warnings();
}

void DebugTestNode::_notification(int p_what) {
	switch (p_what) {
		case NOTIFICATION_POSTINITIALIZE: {
			UtilityFunctions::print("post initialize");
		} break;
		case NOTIFICATION_PREDELETE: {
		} break;
		case NOTIFICATION_EXTENSION_RELOADED: {
		} break;
		case NOTIFICATION_ENTER_TREE: {
		} break;
		case NOTIFICATION_EXIT_TREE: {
		} break;
		case NOTIFICATION_MOVED_IN_PARENT: {
		} break;
		case NOTIFICATION_READY: {
		} break;
		case NOTIFICATION_PAUSED: {
		} break;
		case NOTIFICATION_UNPAUSED: {
		} break;
		case NOTIFICATION_PHYSICS_PROCESS: {
		} break;
		case NOTIFICATION_PROCESS: {
		} break;
		case NOTIFICATION_PARENTED: {
		} break;
		case NOTIFICATION_UNPARENTED: {
		} break;
		case NOTIFICATION_SCENE_INSTANTIATED: {
			UtilityFunctions::print("scene instantiated");
		} break;
		case NOTIFICATION_DRAG_BEGIN: {
		} break;
		case NOTIFICATION_DRAG_END: {
		} break;
		case NOTIFICATION_PATH_RENAMED: {
		} break;
		case NOTIFICATION_CHILD_ORDER_CHANGED: {
		} break;
		case NOTIFICATION_INTERNAL_PROCESS: {
		} break;
		case NOTIFICATION_INTERNAL_PHYSICS_PROCESS: {
		} break;
		case NOTIFICATION_POST_ENTER_TREE: {
		} break;
		case NOTIFICATION_DISABLED: {
		} break;
		case NOTIFICATION_ENABLED: {
		} break;
		case NOTIFICATION_RESET_PHYSICS_INTERPOLATION: {
		} break;
		case NOTIFICATION_EDITOR_PRE_SAVE: {
		} break;
		case NOTIFICATION_EDITOR_POST_SAVE: {
		} break;
		case NOTIFICATION_WM_MOUSE_ENTER: {
		} break;
		case NOTIFICATION_WM_MOUSE_EXIT: {
		} break;
		case NOTIFICATION_WM_WINDOW_FOCUS_IN: {
		} break;
		case NOTIFICATION_WM_WINDOW_FOCUS_OUT: {
		} break;
		case NOTIFICATION_WM_CLOSE_REQUEST: {
		} break;
		case NOTIFICATION_WM_GO_BACK_REQUEST: {
		} break;
		case NOTIFICATION_WM_SIZE_CHANGED: {
		} break;
		case NOTIFICATION_WM_DPI_CHANGE: {
		} break;
		case NOTIFICATION_VP_MOUSE_ENTER: {
		} break;
		case NOTIFICATION_VP_MOUSE_EXIT: {
		} break;
		case NOTIFICATION_OS_MEMORY_WARNING: {
		} break;
		case NOTIFICATION_TRANSLATION_CHANGED: {
		} break;
		case NOTIFICATION_WM_ABOUT: {
		} break;
		case NOTIFICATION_CRASH: {
		} break;
		case NOTIFICATION_OS_IME_UPDATE: {
		} break;
		case NOTIFICATION_APPLICATION_RESUMED: {
		} break;
		case NOTIFICATION_APPLICATION_PAUSED: {
		} break;
		case NOTIFICATION_APPLICATION_FOCUS_IN: {
		} break;
		case NOTIFICATION_APPLICATION_FOCUS_OUT: {
		} break;
		case NOTIFICATION_TEXT_SERVER_CHANGED: {
		} break;
	}
}
