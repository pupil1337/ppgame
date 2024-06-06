#include "gm.h"

#include <thirdpart/imgui/imgui.h>
#include <thirdpart/imgui/imgui_internal.h>
#include <godot_cpp/classes/os.hpp>
#include <godot_cpp/classes/performance.hpp>
#include <godot_cpp/variant/callable_method_pointer.hpp>

GM* GM::singleton = nullptr;

GM::GM() {
	singleton = this;
	thread.instantiate();
}

void GM::_notification(int p_what) {
	if (p_what == NOTIFICATION_POSTINITIALIZE) {
		thread->start(callable_mp(this, &self_type::_imgui_thread));
	}
}

GM::~GM() {
	singleton = nullptr;
	running = false;

	thread->wait_to_finish();
	thread.unref();
}

GM* GM::get_singleton() {
	return singleton;
}

void GM::_imgui_thread() {
	running = true;

	_imgui_backend_initialize();
	while (running) {
		_imgui_backend_flush_begin();

		_flush_impl();

		_imgui_backend_flush_end();

		OS::get_singleton()->delay_msec(16);
	}
	_imgui_backend_terminate();
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

		// performance
		if (Performance* performance = Performance::get_singleton()) {
			double fps = performance->get_monitor(Performance::Monitor::TIME_FPS);
			double process = performance->get_monitor(Performance::Monitor::TIME_PROCESS);
			double physics_process = performance->get_monitor(Performance::Monitor::TIME_PHYSICS_PROCESS);
			ImGui::Text("FPS: %d", (int)fps);
			ImGui::Text("Process: %.2f ms", process * 1000.0);
			ImGui::Text("Physics Process: %.2f ms", physics_process * 1000.0);
		}

		ImGui::End();
	}
}
