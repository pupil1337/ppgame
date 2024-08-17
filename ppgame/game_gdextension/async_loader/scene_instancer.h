#ifndef SCENE_INSTANCER_H
#define SCENE_INSTANCER_H

#include <godot_cpp/classes/mutex.hpp>
#include <godot_cpp/classes/object.hpp>
#include <godot_cpp/classes/packed_scene.hpp>
#include <godot_cpp/classes/ref.hpp>
#include <godot_cpp/classes/thread.hpp>
#include <godot_cpp/classes/wrapped.hpp>
#include <godot_cpp/templates/vector.hpp>
#include <godot_cpp/variant/callable.hpp>
using namespace godot;

class AsyncLoader;

//! 场景实例化器
/*!
 * 开一个线程，将PackedScene实例化为Node
 */
class SceneInstancer : public Object {
	GDCLASS(SceneInstancer, Object)

	friend AsyncLoader;

	struct InstancerData {
		Ref<PackedScene> packed_scene;
		Callable callback;
	};

private:
	//! 增加需要实例化的PackedScene
	/*!
	 * \param p_packed_scene 需要实例化的PackedScene
	 * \param p_callback 实例化完成回调, 参数:Node
	 */
	void add_instancer_data(Ref<PackedScene> p_packed_scene, const Callable& p_callback);

	//! 实例化-线程
	void _instancer_thread();

public:
	SceneInstancer();
	~SceneInstancer();

private:
	bool running = false;
	Ref<Thread> thread;

	Vector<InstancerData> to_instances;
	Ref<Mutex> to_instances_mutex;

	// ------------------------------------------

protected:
	static void _bind_methods() {}
	void _notification(int p_what);
};

#endif // SCENE_INSTANCER_H
