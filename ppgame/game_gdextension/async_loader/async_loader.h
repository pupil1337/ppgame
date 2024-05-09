#ifndef ASYNC_LOADER_H
#define ASYNC_LOADER_H

#include <godot_cpp/classes/node.hpp>
#include <godot_cpp/classes/object.hpp>
#include <godot_cpp/classes/packed_scene.hpp>
#include <godot_cpp/classes/ref.hpp>
#include <godot_cpp/classes/wrapped.hpp>
#include <godot_cpp/templates/hash_map.hpp>
#include <godot_cpp/templates/vector.hpp>
#include <godot_cpp/variant/callable.hpp>
#include <godot_cpp/variant/string.hpp>
using namespace godot;

class SceneLoader;
class SceneInstancer;

class AsyncLoader : public Object {
	GDCLASS(AsyncLoader, Object)

private:
	static AsyncLoader* singleton;

public:
	static AsyncLoader* get_singleton();

	void instance(const String& p_path, const Callable& p_callback);

private:
	void _load_callback(Ref<PackedScene> p_packed_scene);
	void _instance_callback(Node* p_node);

public:
	AsyncLoader();
	~AsyncLoader();

private:
	SceneLoader* loader = nullptr;
	SceneInstancer* instancer = nullptr;

	HashMap<String, Vector<Callable>> path2callbacks;

	// ------------------------------------------

protected:
	static void _bind_methods() {}
};

#endif // ASYNC_LOADER_H
