#ifndef ACTOR_H
#define ACTOR_H

#include <godot_cpp/classes/object.hpp>
#include <godot_cpp/core/error_macros.hpp>
#include <godot_cpp/templates/hash_map.hpp>
#include <godot_cpp/variant/string_name.hpp>
using namespace godot;

class Component;

//! Actor类
/*!
 * 游戏中某个实体将会多继承自Actor，用于管理Component
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
	//! 添加组件
	/*!
	 * 仅在Component被附加到Actor上时，从Component中自动调用
	 * \param p_component 新组件
	 * \return 是否添加成功
	 */
	bool add_component(Component* p_component);

public:
	Actor() {}

private:
	HashMap<StringName, Component*> components; //!< 拥有的组件: StringName -> Component*
};

#endif // ACTOR_H
