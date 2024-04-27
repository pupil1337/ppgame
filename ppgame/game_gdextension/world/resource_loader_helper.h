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
#include <godot_cpp/variant/callable.hpp>
#include <godot_cpp/variant/string.hpp>
using namespace godot;

typedef void (*ResourceLoadedCallback)(Ref<Resource> p_resource);

class ResourceLoaderHelper : public Object {
	GDCLASS(ResourceLoaderHelper, Object)
	typedef Object super;

private:
	static ResourceLoaderHelper* singleton;

public:
	static ResourceLoaderHelper* get_singleton();

	Ref<Resource> load(const String& path, const String& type_hint = String(), ResourceLoader::CacheMode cache_mode = ResourceLoader::CacheMode::CACHE_MODE_REUSE);

	Error load_threaded_request(const String& path, ResourceLoadedCallback callback = nullptr, const String& type_hint = String(), bool use_sub_threads = false, ResourceLoader::CacheMode cache_mode = ResourceLoader::CacheMode::CACHE_MODE_REUSE);

	std::function<void()> testfunc;
	ResourceLoadedCallback testfunc2;
	void AAA(std::function<void(Ref<Resource>)> callback);

	void flush_queries();

	ResourceLoaderHelper();
	~ResourceLoaderHelper();

private:
	ResourceLoader* loader = nullptr;
	HashMap<String, HashSet<ResourceLoadedCallback>> loading_paths;

	// ------------------------------------------

protected:
	static void _bind_methods() {}
};

#endif // RESOURCE_LOADER_HELPER_H
