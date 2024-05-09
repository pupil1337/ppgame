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

struct InstancerData {
	Ref<PackedScene> packed_scene;
	Callable callback;
};

class AsyncLoader;

class SceneInstancer : public Object {
	GDCLASS(SceneInstancer, Object)

	friend AsyncLoader;

private:
	void add_instancer_data(Ref<PackedScene> p_packed_scene, const Callable& p_callback);
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
	void _notification(int p_what);
	static void _bind_methods() {}
};

#endif // SCENE_INSTANCER_H
