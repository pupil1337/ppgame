#include "resource_loader_helper.h"
#include "godot_cpp/variant/array.hpp"

#include <functional>
#include <godot_cpp/classes/global_constants.hpp>
#include <godot_cpp/classes/ref.hpp>
#include <godot_cpp/classes/resource.hpp>
#include <godot_cpp/classes/resource_loader.hpp>
#include <godot_cpp/core/error_macros.hpp>
#include <godot_cpp/templates/hash_map.hpp>
#include <godot_cpp/templates/hash_set.hpp>
#include <godot_cpp/templates/vector.hpp>
#include <godot_cpp/variant/string.hpp>

ResourceLoaderHelper* ResourceLoaderHelper::singleton = nullptr;

ResourceLoaderHelper::ResourceLoaderHelper() {
	singleton = this;

	loader = ResourceLoader::get_singleton();
}

ResourceLoaderHelper::~ResourceLoaderHelper() {
	singleton = nullptr;
}

ResourceLoaderHelper* ResourceLoaderHelper::get_singleton() {
	return singleton;
}

Ref<Resource> ResourceLoaderHelper::load(const String& path, const String& type_hint, ResourceLoader::CacheMode cache_mode /* = ResourceLoader::CacheMode::CACHE_MODE_REUSE */) {
	return loader->load(path, type_hint, cache_mode);
}

void ResourceLoaderHelper::load_threaded_request(const String& path, const String& type_hint, const ResourceLoaderCallback& callback, bool use_sub_threads /* = false */, ResourceLoader::CacheMode cache_mode /* = ResourceLoader::CacheMode::CACHE_MODE_REUSE */) {
	if (!loading.has(path)) {
		if (loader->load_threaded_request(path, type_hint, use_sub_threads, cache_mode) == Error::OK) {
			loading.insert(path, Vector<ResourceLoaderCallback>());
		} else {
			callback(ResourceLoader::ThreadLoadStatus::THREAD_LOAD_FAILED, Ref<Resource>(), 0.0);
			ERR_FAIL_EDMSG("load_threaded_request:: !token.is_valid()");
		}
	}

	Vector<ResourceLoaderCallback>& callbacks = loading.get(path);
	callbacks.push_back(callback);
}

void ResourceLoaderHelper::flush_queries() {
	Vector<String> need_delete_paths;
	for (HashMap<String, Vector<ResourceLoaderCallback>>::ConstIterator it = loading.begin(); it != loading.end(); ++it) {
		const String& path = it->key;
		const Vector<ResourceLoaderCallback>& callbacks = it->value;

		Array progress;
		ResourceLoader::ThreadLoadStatus load_status = loader->load_threaded_get_status(path, progress);
		switch (load_status) {
			case ResourceLoader::ThreadLoadStatus::THREAD_LOAD_INVALID_RESOURCE:
			case ResourceLoader::ThreadLoadStatus::THREAD_LOAD_FAILED:
				for (int i = 0; i < callbacks.size(); ++i) {
					callbacks[i](load_status, Ref<Resource>(), 0.0);
				}
				need_delete_paths.push_back(path);
				break;
			case ResourceLoader::ThreadLoadStatus::THREAD_LOAD_IN_PROGRESS:
				for (int i = 0; i < callbacks.size(); ++i) {
					callbacks[i](load_status, Ref<Resource>(), progress[0]);
				}
				break;
			case ResourceLoader::ThreadLoadStatus::THREAD_LOAD_LOADED:
				for (int i = 0; i < callbacks.size(); ++i) {
					Ref<Resource> resource = loader->load_threaded_get(path);
					if (resource.is_valid()) {
						callbacks[i](load_status, resource, progress[0]);
					} else {
						callbacks[i](ResourceLoader::ThreadLoadStatus::THREAD_LOAD_FAILED, resource, 0.0);
					}
				}
				need_delete_paths.push_back(path);
				break;
		}
	}

	for (int i = 0; i < need_delete_paths.size(); ++i) {
		loading.erase(need_delete_paths[i]);
	}
}
