#include "scene_loader.h"

#include <godot_cpp/classes/os.hpp>
#include <godot_cpp/classes/packed_scene.hpp>
#include <godot_cpp/classes/ref.hpp>
#include <godot_cpp/classes/resource_loader.hpp>
#include <godot_cpp/templates/vector.hpp>
#include <godot_cpp/variant/callable.hpp>
#include <godot_cpp/variant/callable_method_pointer.hpp>
#include <godot_cpp/variant/string.hpp>

SceneLoader::SceneLoader() {
	to_loads_mutex.instantiate();
	thread.instantiate();
}

void SceneLoader::_notification(int p_what) {
	if (p_what == NOTIFICATION_POSTINITIALIZE) {
		thread->start(callable_mp(this, &self_type::_loader_thread));
	}
}
SceneLoader::~SceneLoader() {
	running = false;

	thread->wait_to_finish();
	thread.unref();
}

void SceneLoader::add_loader_data(const String& p_path, const Callable& p_callback) {
	LoaderData loader_data = { p_path, p_callback };

	to_loads_mutex->lock();
	to_loads.push_back(loader_data);
	to_loads_mutex->unlock();
}

void SceneLoader::_loader_thread() {
	running = true;

	while (running) {
		to_loads_mutex->lock();
		Vector<LoaderData> load_datas = to_loads.duplicate();
		to_loads.clear();
		to_loads_mutex->unlock();

		for (int i = 0; i < load_datas.size(); ++i) {
			const LoaderData& data = load_datas[i];
			// TODO 使用scene_cache
			Ref<PackedScene> packed_scene = ResourceLoader::get_singleton()->load(data.path, PackedScene::get_class_static());
			data.callback.call_deferred(packed_scene);
		}

		OS::get_singleton()->delay_msec(16);
	}
}
