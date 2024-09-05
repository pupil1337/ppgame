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
