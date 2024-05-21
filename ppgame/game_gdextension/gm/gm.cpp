#include "gm.h"

#include <thirdpart/imgui/imgui.h>
#include <thirdpart/imgui/imgui_internal.h>

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

		ImGui::End();
	}
}
