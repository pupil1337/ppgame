#ifndef ACTOR_H
#define ACTOR_H

#include <godot_cpp/classes/object.hpp>
#include <godot_cpp/core/error_macros.hpp>
#include <godot_cpp/templates/hash_map.hpp>
#include <godot_cpp/variant/string_name.hpp>
using namespace godot;

class Component;

//! 无父类
/*!
 * 游戏中某个实体godot::Node将会多继承自Actor，用于管理Component
 */
class Actor {
	friend Component;

public:
	//! 获取组件
	/*!
	 * 通过组件类型获取组件
	 */
	template <typename T>
	T* get_component() const {
		HashMap<StringName, Component*>::ConstIterator it = components.find(T::get_class_static());
		if (it != components.end()) {
			return Object::cast_to<T>(it->value);
		}

		ERR_FAIL_V_EDMSG(nullptr, "Cannot get component:" + T::get_class_static());
	}

private:
	HashMap<StringName, Component*> components; //!< 组件映射：StringName -> Component*

private:
	//! 添加组件
	/*!
	 * 仅在Component被附加到Actor上时，从Component中自动调用
	 */
	void add_component(Component* p_component);
};

#endif // ACTOR_H
