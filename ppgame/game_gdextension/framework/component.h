#ifndef COMPONENT_H
#define COMPONENT_H

#include <godot_cpp/classes/node.hpp>
#include <godot_cpp/classes/wrapped.hpp>
using namespace godot;

class Actor;

//! Component类
/*!
 * 用于实现抽象的业务逻辑: 本质是一个Node节点用于附加, 在其中实现业务逻辑
 */
class Component : public Node {
	GDCLASS(Component, Node)

private:
	//! 注册此组件
	/*!
	 * 将此组件注册到Actor上
	 * _notification()->NOTIFICATION_PARENTED 时自动调用
	 * \param p_node 需要找到父节点为Actor类的Node. 初始值为this, 如果父节点不是Actor则递归父节点查找
	 * \return 是否注册成功
	 */
	bool _register_component(Node* p_node);

public:
	Component() {}

protected:
	Actor* actor = nullptr; //!< 拥有者

	// ------------------------------------------

protected:
	static void _bind_methods() {}
	void _notification(int p_what);
};

#endif // COMPONENT_H
