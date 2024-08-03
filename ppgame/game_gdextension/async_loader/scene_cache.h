#ifndef SCENE_CACHE_H
#define SCENE_CACHE_H

#include <godot_cpp/classes/object.hpp>
#include <godot_cpp/classes/packed_scene.hpp>
#include <godot_cpp/classes/ref.hpp>
#include <godot_cpp/classes/wrapped.hpp>
#include <godot_cpp/templates/hash_map.hpp>
#include <godot_cpp/variant/string.hpp>
using namespace godot;

//! 场景缓存器 (待实现)
class SceneCache : public Object {
	GDCLASS(SceneCache, Object)

private:
	HashMap<String, Ref<PackedScene>> cache;

	// ------------------------------------------

protected:
	static void _bind_methods() {}
};

#endif // SCENE_CACHE_H
