#ifndef WORLD_H
#define WORLD_H

#include <godot_cpp/classes/node.hpp>
#include <godot_cpp/classes/wrapped.hpp>
#include <godot_cpp/templates/vector.hpp>
#include <godot_cpp/variant/string.hpp>
using namespace godot;

class Level;
class Player;

//! World类
/*!
 * 游戏的根节点
 */
class World : public Node {
	GDCLASS(World, Node)

public:
	//! 获取World
	/*!
	 * \param p_inside_node 树上的某节点
	 * \return 得到的World
	 */
	static World* get_world(Node* p_inside_node);

	//! 切换关卡
	/*!
	 * \param p_level 关卡路径
	 * \param p_player_start 关卡中角色生成点
	 */
	void change_level(const String& p_level, const String& p_player_start);

private:
	//! 切换关卡的具体实现
	/*!
	 * \param p_node 加载并实例化后的关卡
	 * \param p_player_start 关卡中角色生成点
	 */
	void _change_level_implement(Node* p_node, const String& p_player_start);

public:
	World() {}

private:
	Level* curr_level = nullptr; //!< 当前关卡
	Player* player = nullptr; //!< 角色

	// ------------------------------------------

public:
	virtual void _enter_tree() override;
	virtual void _ready() override;
	virtual void _process(double delta) override;
	virtual void _exit_tree() override;

protected:
	void _notification(int p_what);
	static void _bind_methods() {}
};

#endif // WORLD_H
