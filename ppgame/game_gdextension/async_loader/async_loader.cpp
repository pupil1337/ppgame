#include "async_loader.h"

#include <godot_cpp/classes/node.hpp>
#include <godot_cpp/classes/object.hpp>
#include <godot_cpp/classes/packed_scene.hpp>
#include <godot_cpp/classes/ref.hpp>
#include <godot_cpp/classes/resource_loader.hpp>
#include <godot_cpp/core/memory.hpp>
#include <godot_cpp/templates/vector.hpp>
#include <godot_cpp/variant/callable.hpp>
#include <godot_cpp/variant/callable_method_pointer.hpp>
#include <godot_cpp/variant/string.hpp>

#include "async_loader/scene_instancer.h"
#include "async_loader/scene_loader.h"

AsyncLoader* AsyncLoader::singleton = nullptr;

AsyncLoader::AsyncLoader() {
	singleton = this;

	loader = memnew(SceneLoader);
	instancer = memnew(SceneInstancer);
}

AsyncLoader::~AsyncLoader() {
	singleton = nullptr;

	memdelete(loader);
	memdelete(instancer);
}

AsyncLoader* AsyncLoader::get_singleton() {
	return singleton;
}

Node* AsyncLoader::instance(const String& p_path) {
	Node* res = nullptr;

	// TODO 使用scene_cache
	Ref<PackedScene> packed_scene = ResourceLoader::get_singleton()->load(p_path, PackedScene::get_class_static());
	if (packed_scene.is_valid()) {
		res = packed_scene->instantiate();
	}

	return res;
}

void AsyncLoader::instance(const String& p_path, const Callable& p_callback) {
	if (!path2callbacks.has(p_path)) {
		path2callbacks.insert(p_path, Vector<Callable>());
	}
	path2callbacks.get(p_path).push_back(p_callback);

	loader->add_loader_data(p_path, callable_mp(this, &self_type::_load_callback));
}

void AsyncLoader::_load_callback(Ref<PackedScene> p_packed_scene) {
	instancer->add_instancer_data(p_packed_scene, callable_mp(this, &self_type::_instance_callback));
}

void AsyncLoader::_instance_callback(Node* p_node) {
	const String& node_path = p_node->get_scene_file_path();
	if (path2callbacks.has(node_path)) {
		const Vector<Callable>& callbacks = path2callbacks.get(node_path);
		for (int i = 0; i < callbacks.size(); ++i) {
			const Callable& callback = callbacks[i];
			if (callback.is_valid()) {
				callback.call_deferred(p_node);
			}
		}

		path2callbacks.erase(node_path);
	}
}
