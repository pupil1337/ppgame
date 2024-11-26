# class_name AsyncLoader 
# autoload
extends Node

var scene_loader: SceneLoader
var scene_instancer: SceneInstancer;

var async_instance_callbacks: Dictionary # { path: [Callback, ...], ... }


func _init() -> void:
	scene_loader = SceneLoader.new(_load_callback)
	scene_instancer = SceneInstancer.new(_instance_callback)


func _notification(what: int) -> void:
	if what == NOTIFICATION_PREDELETE:
		scene_loader.free_wait_thread_to_finish().free()
		scene_instancer.free_wait_thread_to_finish().free()


## 根据路径实例化(同步)
func instance(p_path: String) -> Node:
	var resource: Resource = ResourceLoader.load(p_path)
	if resource is PackedScene:
		return (resource as PackedScene).instantiate()
	return null


## 根据路径实例化(异步)
## [param p_path]: 路径
## [param p_callback]: 回调函数, 参数: Node
func instance_async(p_path: String, p_callback: Callable) -> void:
	if not async_instance_callbacks.has(p_path):
		async_instance_callbacks[p_path] = Array([], TYPE_CALLABLE, "", null)
	@warning_ignore("UNSAFE_CAST")
	(async_instance_callbacks[p_path] as Array[Callable]).push_back(p_callback)
	
	scene_loader.add_loader_data(p_path)


func _load_callback(p_packed_scene: PackedScene) -> void:
	if async_instance_callbacks.has(p_packed_scene.resource_path):
		@warning_ignore("UNSAFE_CAST")
		for i: int in range((async_instance_callbacks[p_packed_scene.resource_path] as Array[Callable]).size()):
			scene_instancer.add_instance_data(p_packed_scene)


func _instance_callback(p_path: String, p_node: Node) -> void:
	if not async_instance_callbacks.has(p_path):
		p_node.queue_free()
		return
	
	var callbacks: Array[Callable] = async_instance_callbacks[p_path]
	var callback: Callable = callbacks.pop_front()
	if callback:
		callback.call(p_node)
	
	if callbacks.is_empty():
		@warning_ignore("return_value_discarded")
		async_instance_callbacks.erase(p_path)


#region
class SceneLoader extends Object:
	
	var running: bool
	var thread: Thread
	
	var to_loads: PackedStringArray
	var to_loads_mutex: Mutex
	
	var scene_cache: Dictionary # { path: PackedScene, ... }
	
	var loaded_callable: Callable
	
	
	func _init(p_loaded_callable: Callable) -> void:
		loaded_callable = p_loaded_callable
		
		to_loads_mutex = Mutex.new()
		thread = Thread.new()
		@warning_ignore("RETURN_VALUE_DISCARDED")
		thread.start(_loader_thread)
	
	
	func free_wait_thread_to_finish() -> SceneLoader:
		running = false
		if thread.is_started():
			thread.wait_to_finish()
			thread = null
		return self
	
	
	func add_loader_data(p_path: String) -> void:
		if scene_cache.has(p_path):
			loaded_callable.call(scene_cache[p_path])
		
		to_loads_mutex.lock()
		if not to_loads.has(p_path):
			@warning_ignore("return_value_discarded")
			to_loads.push_back(p_path)
		to_loads_mutex.unlock()
	
	
	func _loader_thread() -> void:
		running = true
		
		while running:
			to_loads_mutex.lock()
			var load_datas: PackedStringArray = to_loads.duplicate()
			to_loads.clear()
			to_loads_mutex.unlock()
			
			for path: String in load_datas:
				scene_cache[path] = ResourceLoader.load(path)
				loaded_callable.call_deferred(scene_cache[path])
			
			OS.delay_msec(16)
		
		print("SceneLoader: _loader_thread() end")
#endregion


#region
class SceneInstancer extends Object:
	
	var running: bool
	var thread: Thread
	
	var to_instances: Array[PackedScene]
	var to_instances_mutex: Mutex
	
	var instanced_callable: Callable
	
	
	func _init(p_instanced_callable: Callable) -> void:
		instanced_callable = p_instanced_callable
		
		to_instances_mutex = Mutex.new()
		thread = Thread.new()
		@warning_ignore("RETURN_VALUE_DISCARDED")
		thread.start(_instancer_thread)
	
	
	func free_wait_thread_to_finish() -> SceneInstancer:
		running = false
		if thread.is_started():
			thread.wait_to_finish()
			thread = null
		return self
	
	
	func add_instance_data(p_packed_scene: PackedScene) -> void:
		to_instances_mutex.lock()
		to_instances.push_back(p_packed_scene)
		to_instances_mutex.unlock()
	
	
	func _instancer_thread() -> void:
		running = true
		
		while running:
			to_instances_mutex.lock()
			var instance_datas: Array[PackedScene] = to_instances.duplicate()
			to_instances.clear()
			to_instances_mutex.unlock()
			
			for packed_scene: PackedScene in instance_datas:
				if packed_scene:
					instanced_callable.call_deferred(packed_scene.resource_path, packed_scene.instantiate())
			
			OS.delay_msec(16)
		
		print("SceneInstancer: _instancer_thread() end")
#endregion
