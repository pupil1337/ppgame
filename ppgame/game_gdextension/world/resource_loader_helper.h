#ifndef RESOURCE_LOADER_HELPER_H
#define RESOURCE_LOADER_HELPER_H

#include <functional>
#include <godot_cpp/classes/global_constants.hpp>
#include <godot_cpp/classes/object.hpp>
#include <godot_cpp/classes/ref.hpp>
#include <godot_cpp/classes/resource.hpp>
#include <godot_cpp/classes/resource_loader.hpp>
#include <godot_cpp/classes/wrapped.hpp>
#include <godot_cpp/templates/hash_map.hpp>
#include <godot_cpp/templates/hash_set.hpp>
#include <godot_cpp/templates/vector.hpp>
#include <godot_cpp/variant/callable.hpp>
#include <godot_cpp/variant/string.hpp>
using namespace godot;

class ResourceLoaderHelper : public Object {
	GDCLASS(ResourceLoaderHelper, Object)

	typedef std::function<void(ResourceLoader::ThreadLoadStatus, Ref<Resource>, float)> ResourceLoaderCallback;

private:
	static ResourceLoaderHelper* singleton;

public:
	static ResourceLoaderHelper* get_singleton();

	Ref<Resource> load(const String& path, const String& type_hint, ResourceLoader::CacheMode cache_mode = ResourceLoader::CacheMode::CACHE_MODE_REUSE);

	void load_threaded_request(const String& path, const String& type_hint, const ResourceLoaderCallback& callback, bool use_sub_threads = false, ResourceLoader::CacheMode cache_mode = ResourceLoader::CacheMode::CACHE_MODE_REUSE);

	void flush_queries();

	ResourceLoaderHelper();
	~ResourceLoaderHelper();

private:
	ResourceLoader* loader = nullptr;
	HashMap<String, Vector<ResourceLoaderCallback>> loading;

	// ------------------------------------------

protected:
	static void _bind_methods() {}
};

#endif // RESOURCE_LOADER_HELPER_H
