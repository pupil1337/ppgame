#ifndef NODE_UTILS_H
#define NODE_UTILS_H

#include <godot_cpp/classes/node.hpp>
#include <godot_cpp/classes/object.hpp>
using namespace godot;

//! Node工具
class NodeUtils {
public:
	//! 获取第一个类型为T的父节点
	/*!
	 * \tparam T 查找的父节点类型
	 * \param p_node 查找的起始节点
	 * \return 查找结果
	 */
	template <typename T>
	static T* get_parent_node(Node* p_node) {
		if (p_node) {
			if (Node* parent = p_node->get_parent()) {
				if (parent != p_node) {
					if (T* res = Object::cast_to<T>(parent)) {
						return res;
					} else {
						return get_parent_node<T>(parent);
					}
				}
			}
		}

		return nullptr;
	}
};

#endif // NODE_UTILS_H
