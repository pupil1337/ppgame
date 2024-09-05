#ifndef MONSTER_PATROL_STATE_H
#define MONSTER_PATROL_STATE_H

#include <godot_cpp/classes/wrapped.hpp>
#include <godot_cpp/variant/string_name.hpp>
#include <godot_cpp/variant/vector2.hpp>
using namespace godot;

#include "character/monster/state/monster_state.h"
#include "utils/types.h"

//! 怪物巡逻状态
class MonsterPatrolState : public MonsterState {
	GDCLASS(MonsterPatrolState, MonsterState)

public:
	virtual void enter() override;
	virtual StringName on_process(double delta) override;
	virtual void on_physics_process(double delta) override;
	virtual void exit() override;

private:
	//! 检查玩家是否在视野内
	bool _check_player_in_view();
	//! 更新地面巡逻目标
	void _update_patrol_target_grounded();
	//! 更新空中巡逻目标
	void _update_patrol_target_floating();

private:
	void set_view_length(int p_view_length);
	int get_view_length();
	void set_patrol_radius_floating(int p_patrol_radius_floating);
	int get_patrol_radius_floating();

public:
	MonsterPatrolState();

private:
	int view_length = 200;
	int patrol_radius_floating = 200;

	// Grounded
private:
	Direction patrol_direction_grounded = Direction::None;

	// Floating
private:
	Vector2 patrol_position_floating;

	// ------------------------------------------

protected:
	static void _bind_methods();
};

#endif // MONSTER_PATROL_STATE_H
