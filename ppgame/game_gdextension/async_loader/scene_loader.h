#ifndef SCENE_LOADER_H
#define SCENE_LOADER_H

#include <godot_cpp/classes/mutex.hpp>
#include <godot_cpp/classes/object.hpp>
#include <godot_cpp/classes/ref.hpp>
#include <godot_cpp/classes/thread.hpp>
#include <godot_cpp/classes/wrapped.hpp>
#include <godot_cpp/templates/vector.hpp>
#include <godot_cpp/variant/callable.hpp>
#include <godot_cpp/variant/string.hpp>
using namespace godot;

class AsyncLoader;

//! 场景加载器
/*!
 * 开一个线程, 加载指定path的PackedScene
 */
class SceneLoader : public Object {
	GDCLASS(SceneLoader, Object)

	friend AsyncLoader;

	struct LoaderData {
		String path;
		Callable callback;
	};

private:
	//! 添加需要加载的path
	/*!
	 * \param p_path 需要加载的path
	 * \param p_callback 加载完成回调函数, 参数:PackedScene
	 */
	void add_loader_data(const String& p_path, const Callable& p_callback);

	//! 加载-线程
	void _loader_thread();

public:
	SceneLoader();
	~SceneLoader();

private:
	bool running = false;
	Ref<Thread> thread;

	Vector<LoaderData> to_loads;
	Ref<Mutex> to_loads_mutex;

	// ------------------------------------------

protected:
	void _notification(int p_what);
	static void _bind_methods() {}
};

#endif // SCENE_LOADER_H
