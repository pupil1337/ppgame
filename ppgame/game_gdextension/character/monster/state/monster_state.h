#ifndef MONSTER_STATE_H
#define MONSTER_STATE_H

#include <godot_cpp/classes/navigation_agent2d.hpp>
#include <godot_cpp/classes/wrapped.hpp>
using namespace godot;

#include "fsm/state.h"

class Monster;
class MonsterConcurrentStateMachineComponent;
struct MonsterStateCondition;
class CharacterMovementComponent;

//! 怪物状态基类
class MonsterState : public State {
	GDCLASS(MonsterState, State)

	friend MonsterConcurrentStateMachineComponent;

public:
	MonsterState() {}

protected:
	Monster* monster = nullptr; //!< 怪物
	CharacterMovementComponent* character_movement_component = nullptr; //!< 角色移动组件
	NavigationAgent2D* nav_agent = nullptr; //!< 导航代理
	const MonsterStateCondition* condition = nullptr; //!< 状态条件

	// ------------------------------------------

protected:
	static void _bind_methods() {}
};

#endif // MONSTER_STATE_H
