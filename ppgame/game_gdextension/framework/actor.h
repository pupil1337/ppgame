#ifndef ACTOR_H
#define ACTOR_H

#include <godot_cpp/classes/node.hpp>
#include <godot_cpp/classes/object.hpp>
#include <godot_cpp/core/error_macros.hpp>
#include <godot_cpp/templates/hash_map.hpp>
#include <godot_cpp/variant/string_name.hpp>
#include <godot_cpp/variant/typed_array.hpp>
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

	//! 获取子节点
	/*!
	 * 通过子节点类型获取子节点
	 * \warning 可能有性能问题. 多用于编辑器期间, 因为编辑器期间不会增加/减少Component, 所以通过遍历Children来获取Component
	 */
	template <typename T>
	T* get_child(bool p_include_internal = false) const {
		if (node) {
			T* res = nullptr;

			const TypedArray<Node>& children = node->get_children(p_include_internal);
			for (int i = 0; i < children.size(); ++i) {
				if (T* new_res = Object::cast_to<T>(children[i].operator Object*())) {
					if (res) {
						ERR_FAIL_V_EDMSG(res, "Find more than one child node of type:" + T::get_class_static() + ". so get firstest");
					}
					res = new_res;
				}
			}

			if (res) {
				return res;
			}
		}

		ERR_FAIL_V_EDMSG(nullptr, "Cannot get child:" + T::get_class_static());
	}

	//! 获取父节点actor
	/*!
	 * \param p_node 从哪个节点查找
	 * \return 查找到的第一个actor类型的父节点
	 */
	static Actor* get_parent_actor(Node* p_node);

private:
	//! 添加组件
	/*!
	 * 仅在Component被附加到Actor上时，从Component中自动调用
	 * \param p_component 新组件
	 * \return 是否添加成功
	 */
	bool add_component(Component* p_component);

public:
	Actor() = delete;
	Actor(Node* p_node) :
			node(p_node) {}

private:
	Node* node = nullptr;
	HashMap<StringName, Component*> components; //!< 拥有的组件: StringName -> Component*
};

#endif // ACTOR_H
