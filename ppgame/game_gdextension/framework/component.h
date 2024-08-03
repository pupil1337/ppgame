#ifndef COMPONENT_H
#define COMPONENT_H

#include <godot_cpp/classes/node.hpp>
#include <godot_cpp/classes/wrapped.hpp>
using namespace godot;

class Actor;

//! 继承自Node
/*!
 * 在Component中实现抽象的业务逻辑，本质是一个godot::Node节点
 */
class Component : public Node {
	GDCLASS(Component, Node)

protected:
	Actor* actor = nullptr; //!< 拥有者

private:
	//! 注册此组件
	/*!
	 * _notification()->NOTIFICATION_PARENTED 时自动调用
	 */
	void _register_component(Node* p_node);

	// ------------------------------------------

protected:
	void _notification(int p_what);
	static void _bind_methods() {}
};

#endif // COMPONENT_H
