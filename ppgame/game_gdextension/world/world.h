#ifndef WORLD_H
#define WORLD_H

#include <godot_cpp/classes/node.hpp>
#include <godot_cpp/classes/wrapped.hpp>
#include <godot_cpp/core/defs.hpp>
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

	static World* singleton;

public:
	//! 切换关卡
	/*!
	 * \param p_level 关卡路径
	 * \param p_player_start 关卡中玩家生成点
	 */
	void change_level(const String& p_level, const String& p_player_start);

	_FORCE_INLINE_ Player* get_player() { return player; }

private:
	//! 切换关卡的具体实现
	/*!
	 * \param p_node 加载并实例化后的关卡
	 * \param p_player_start 关卡中玩家生成点
	 */
	void _change_level_implement(Node* p_node, const String& p_player_start);

public:
	World();
	~World();
	static World* get_singleton();

private:
	Level* curr_level = nullptr; //!< 当前关卡
	Player* player = nullptr; //!< 玩家

	// ------------------------------------------

public:
	virtual void _enter_tree() override;
	virtual void _ready() override;
	virtual void _process(double delta) override;
	virtual void _exit_tree() override;

protected:
	static void _bind_methods() {}
	void _notification(int p_what);
};

#endif // WORLD_H
