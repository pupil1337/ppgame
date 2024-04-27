#include "resource_loader_helper.h"

#include <godot_cpp/classes/global_constants.hpp>
#include <godot_cpp/classes/ref.hpp>
#include <godot_cpp/classes/resource.hpp>
#include <godot_cpp/classes/resource_loader.hpp>
#include <godot_cpp/templates/hash_map.hpp>
#include <godot_cpp/templates/hash_set.hpp>
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

Ref<Resource> ResourceLoaderHelper::load(const String& path, const String& type_hint /* = String() */, ResourceLoader::CacheMode cache_mode /* = ResourceLoader::CacheMode::CACHE_MODE_REUSE */) {
	return loader->load(path, type_hint, cache_mode);
}

Error ResourceLoaderHelper::load_threaded_request(const String& path, ResourceLoadedCallback callback /* = nullptr */, const String& type_hint /* = String() */, bool use_sub_threads /* = false */, ResourceLoader::CacheMode cache_mode /* = ResourceLoader::CacheMode::CACHE_MODE_REUSE */) {
	if (callback != nullptr) {
		if (!loading_paths.has(path)) {
			loading_paths.insert(path, HashSet<ResourceLoadedCallback>());
		}

		HashSet<ResourceLoadedCallback>& callbacks = loading_paths.get(path);
		if (!callbacks.has(callback)) {
			callbacks.insert(callback);
		}
	}

	return loader->load_threaded_request(path, type_hint, use_sub_threads, cache_mode);
}

void ResourceLoaderHelper::flush_queries() {
	for (HashMap<String, HashSet<ResourceLoadedCallback>>::Iterator it = loading_paths.begin(); it != loading_paths.end(); ++it) {
		const String& path = it->key;
		const HashSet<ResourceLoadedCallback>& callbacks = it->value;

		ResourceLoader::ThreadLoadStatus load_status = loader->load_threaded_get_status(path);
		switch (load_status) {
			case ResourceLoader::ThreadLoadStatus::THREAD_LOAD_INVALID_RESOURCE:
				break;
			case ResourceLoader::ThreadLoadStatus::THREAD_LOAD_IN_PROGRESS:
				break;
			case ResourceLoader::ThreadLoadStatus::THREAD_LOAD_FAILED:
				break;
			case ResourceLoader::ThreadLoadStatus::THREAD_LOAD_LOADED:
				for (HashSet<ResourceLoadedCallback>::Iterator callback = callbacks.begin(); callback != callbacks.end(); ++callback) {
					(*callback)(loader->load_threaded_get(path));
				}
				break;
		}
	}
}
