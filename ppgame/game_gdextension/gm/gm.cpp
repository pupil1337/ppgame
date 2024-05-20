#include "gm.h"

#include <thirdpart/imgui/imgui.h>
#include <thirdpart/imgui/imgui_internal.h>
#include <godot_cpp/classes/canvas_item.hpp>
#include <godot_cpp/classes/collision_shape2d.hpp>
#include <godot_cpp/classes/engine.hpp>
#include <godot_cpp/classes/node.hpp>
#include <godot_cpp/classes/object.hpp>
#include <godot_cpp/classes/scene_tree.hpp>
#include <godot_cpp/classes/window.hpp>
#include <godot_cpp/variant/typed_array.hpp>

GM* GM::singleton = nullptr;

GM::GM() {
	singleton = this;

	_imgui_backend_initialize();
}

GM::~GM() {
	singleton = nullptr;

	_imgui_backend_terminate();
}

GM* GM::get_singleton() {
	return singleton;
}

void GM::flush() {
	_imgui_backend_flush_begin();

	_flush_impl();

	_imgui_backend_flush_end();
}

void GM::_flush_impl() {
	ImGuiIO& io = ImGui::GetIO();

	if (show_demo_window) {
		ImGui::ShowDemoWindow(&show_demo_window);
	}

	{
		ImGuiWindowClass topmost;
		topmost.ClassId = ImHashStr("TopMost");
		topmost.ViewportFlagsOverrideSet = ImGuiViewportFlags_TopMost;
		ImGui::SetNextWindowClass(&topmost);

		ImGui::Begin("GM");

		ImGui::Text("Hello, world!");
		ImGui::Checkbox("Demo Window", &show_demo_window);

		ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / io.Framerate, io.Framerate);

		// - show debug collision
		if (SceneTree* tree = Object::cast_to<SceneTree>(Engine::get_singleton()->get_main_loop())) {
			bool show_debug_collision = tree->is_debugging_collisions_hint();
			if (ImGui::Checkbox("show_debug_collision", &show_debug_collision)) {
				tree->set_debug_collisions_hint(show_debug_collision);

				TypedArray<Node> nodes = tree->get_root()->find_children({}, Node::get_class_static(), true, false);
				for (int i = 0; i < nodes.size(); ++i) {
					if (CollisionShape2D* shape = Object::cast_to<CollisionShape2D>(nodes[i])) {
						shape->propagate_notification(CanvasItem::NOTIFICATION_DRAW);
					}
				}
			}
		}

		ImGui::End();
	}
}
