#include "scene_instancer.h"

#include <godot_cpp/classes/node.hpp>
#include <godot_cpp/classes/os.hpp>
#include <godot_cpp/classes/packed_scene.hpp>
#include <godot_cpp/classes/ref.hpp>
#include <godot_cpp/templates/vector.hpp>
#include <godot_cpp/variant/callable.hpp>
#include <godot_cpp/variant/callable_method_pointer.hpp>

SceneInstancer::SceneInstancer() {
	to_instances_mutex.instantiate();
	thread.instantiate();
}

void SceneInstancer::_notification(int p_what) {
	if (p_what == NOTIFICATION_POSTINITIALIZE) {
		thread->start(callable_mp(this, &self_type::_instancer_thread));
	}
}

SceneInstancer::~SceneInstancer() {
	running = false;

	thread->wait_to_finish();
	thread.unref();
}

void SceneInstancer::add_instancer_data(Ref<PackedScene> p_packed_scene, const Callable& p_callback) {
	InstancerData instancer_data = { p_packed_scene, p_callback };

	to_instances_mutex->lock();
	to_instances.push_back(instancer_data);
	to_instances_mutex->unlock();
}

void SceneInstancer::_instancer_thread() {
	running = true;

	while (running) {
		to_instances_mutex->lock();
		Vector<InstancerData> instancer_data = to_instances.duplicate();
		to_instances.clear();
		to_instances_mutex->unlock();

		for (int i = 0; i < instancer_data.size(); ++i) {
			const InstancerData& data = instancer_data[i];
			Node* node = data.packed_scene->instantiate();
			if (data.callback.is_valid()) {
				data.callback.call_deferred(node);
			}
		}

		OS::get_singleton()->delay_msec(16);
	}
}
