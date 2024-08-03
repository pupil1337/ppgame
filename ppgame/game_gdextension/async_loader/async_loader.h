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

//! 异步加载器
/*!
 * 可以异步/同步加载并且实例化某节点的单例
 */
class AsyncLoader : public Object {
	GDCLASS(AsyncLoader, Object)

private:
	static AsyncLoader* singleton;

public:
	static AsyncLoader* get_singleton();

	//! 同步实例化
	/*!
	 * \param p_path 路径
	 * \return 实例化后的节点
	 */
	Node* instance(const String& p_path);

	//! 异步实例化
	/*!
	 * \param p_path 路径
	 * \param p_callback 实例化回调函数, 参数:Node
	 */
	void instance(const String& p_path, const Callable& p_callback);

private:
	//! PackedScene加载完成回调
	/*!
	 * 通过path异步加载PackedScene
	 * \param p_packed_scene 异步加载的PackedScene
	 * \param p_path 异步加载的path
	 */
	void _load_callback(Ref<PackedScene> p_packed_scene, const String& p_path);

	//! Node实例化完成回调
	/*!
	 * 通过PackedScene异步实例化Node
	 * \param p_node 异步实例化的Node
	 * \param p_path 异步实例化的path
	 */
	void _instance_callback(Node* p_node, const String& p_path);

public:
	AsyncLoader();
	~AsyncLoader();

private:
	SceneLoader* loader = nullptr; //!< 场景加载器
	SceneInstancer* instancer = nullptr; //!< 场景实例化器

	HashMap<String, Vector<Callable>> path2callbacks; //!< 需要异步加载的路径 -> 回调函数

	// ------------------------------------------

protected:
	static void _bind_methods() {}
};

#endif // ASYNC_LOADER_H
