#ifndef GM_H
#define GM_H

#include <thirdparty/imgui/imgui.h>
#include <thirdparty/imgui/imgui_impl_glfw.h>
#include <godot_cpp/classes/object.hpp>
#include <godot_cpp/classes/ref.hpp>
#include <godot_cpp/classes/thread.hpp>
#include <godot_cpp/classes/wrapped.hpp>
using namespace godot;

// warning!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
// 这个原先是用于gdextension显示GM的, 但是现在业务逻辑都写在gdscript中, 并且想要将ImGui的接口函数导出到gdscript中很麻烦, 所以这个类废弃了
// 代码还留着的目的是 这个是一个gdextension接入第三方库的例子

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
	static void _bind_methods() {}
	void _notification(int p_what);
};

#endif // GM_H
