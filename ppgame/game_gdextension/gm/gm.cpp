#include "gm.h"

#include <GLFW/glfw3.h>
#ifdef WINDOWS_ENABLED
#include <gl/gl.h>
#else
#include <GL/gl.h>
#endif
#include <thirdparty/imgui/imgui.h>
#include <thirdparty/imgui/imgui_impl_glfw.h>
#include <thirdparty/imgui/imgui_impl_opengl3.h>
#include <thirdparty/imgui/imgui_internal.h>
#include <cstdio>

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

static void glfw_error_callback(int error, const char* description) {
	fprintf(stderr, "GLFW Error %d: %s\n", error, description);
}

void GM::_imgui_backend_initialize() {
	glfwSetErrorCallback(glfw_error_callback);
	if (glfwInit()) {
		// GL 3.0 + GLSL 130
		const char* glsl_version = "#version 130";
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
		// glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // 3.2+ only
		// glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // 3.0+ only (Mac OS X)
#ifdef WINDOWS_ENABLED
		glfwWindowHint(GLFW_VISIBLE, GLFW_FALSE);
#endif

		// Create window with graphics context
		window = glfwCreateWindow(1280, 720, "GM", nullptr, nullptr);
		if (window != nullptr) {
			glfwMakeContextCurrent(window);
			glfwSwapInterval(1); // Enable vsync

			// Setup Dear ImGui context
			IMGUI_CHECKVERSION();
			ImGui::CreateContext();
			ImGuiIO& io = ImGui::GetIO();
			io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard; // Enable Keyboard Controls
			// io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad; // Enable Gamepad Controls
#ifdef WINDOWS_ENABLED
			io.ConfigFlags |= ImGuiConfigFlags_DockingEnable; // Enable Docking
			io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable; // Enable Multi-Viewport / Platform Windows
			io.ConfigViewportsNoAutoMerge = true;
			io.ConfigViewportsNoTaskBarIcon = true;
#endif

			// Setup Dear ImGui style
			ImGui::StyleColorsDark();
			// ImGui::StyleColorsLight();

			// When viewports are enabled we tweak WindowRounding/WindowBg so platform windows can look identical to regular ones.
			ImGuiStyle& style = ImGui::GetStyle();
			if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable) {
				style.WindowRounding = 0.0f;
				style.Colors[ImGuiCol_WindowBg].w = 1.0f;
			}

			// Setup Platform/Renderer backends
			ImGui_ImplGlfw_InitForOpenGL(window, true);
			ImGui_ImplOpenGL3_Init(glsl_version);
		}
	}
}

void GM::_imgui_backend_flush_begin() {
	// Poll and handle events (inputs, window resize, etc.)
	// You can read the io.WantCaptureMouse, io.WantCaptureKeyboard flags to tell if dear imgui wants to use your inputs.
	// - When io.WantCaptureMouse is true, do not dispatch mouse input data to your main application, or clear/overwrite your copy of the mouse data.
	// - When io.WantCaptureKeyboard is true, do not dispatch keyboard input data to your main application, or clear/overwrite your copy of the keyboard data.
	// Generally you may always pass all inputs to dear imgui, and hide them from your application based on those two flags.
	glfwPollEvents();

	// Start the Dear ImGui frame
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();
}

void GM::_imgui_backend_flush_end() {
	ImGuiIO& io = ImGui::GetIO();

	// Rendering
	ImGui::Render();
	int display_w, display_h;
	glfwGetFramebufferSize(window, &display_w, &display_h);
	glViewport(0, 0, display_w, display_h);
	glClearColor(0.45f, 0.55f, 0.60f, 1.00f);
	glClear(GL_COLOR_BUFFER_BIT);
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

	// Update and Render additional Platform Windows
	// (Platform functions may change the current OpenGL context, so we save/restore it to make it easier to paste this code elsewhere.
	//  For this specific demo app we could also call glfwMakeContextCurrent(window) directly)
	if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable) {
		GLFWwindow* backup_current_context = glfwGetCurrentContext();
		ImGui::UpdatePlatformWindows();
		ImGui::RenderPlatformWindowsDefault();
		glfwMakeContextCurrent(backup_current_context);
	}

	glfwSwapBuffers(window);
}

void GM::_imgui_backend_terminate() {
	// Cleanup
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();

	glfwDestroyWindow(window);
	glfwTerminate();
}
