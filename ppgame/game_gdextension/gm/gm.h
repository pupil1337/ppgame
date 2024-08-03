#ifndef GM_H
#define GM_H

#include <thirdpart/imgui/imgui.h>
#include <thirdpart/imgui/imgui_impl_glfw.h>
#include <godot_cpp/classes/object.hpp>
#include <godot_cpp/classes/ref.hpp>
#include <godot_cpp/classes/thread.hpp>
#include <godot_cpp/classes/wrapped.hpp>
using namespace godot;

class World;

//! ImGui实现的GM
class GM : public Object {
	GDCLASS(GM, Object)

	static GM* singleton;

public:
	static GM* get_singleton();

private:
	//! ImGui-线程
	void _imgui_thread();
	//! ImGui初始化
	void _imgui_backend_initialize();
	//! ImGui刷新begin
	void _imgui_backend_flush_begin();
	//! ImGui刷新GM
	void _flush_impl();
	//! ImGui刷新end
	void _imgui_backend_flush_end();
	//! ImGui终止
	void _imgui_backend_terminate();

public:
	GM();
	~GM();

private:
	bool running = false;
	Ref<Thread> thread;

	GLFWwindow* window = nullptr;
	bool show_demo_window = false;

	// ------------------------------------------

protected:
	void _notification(int p_what);
	static void _bind_methods() {}
};

#endif // GM_H
