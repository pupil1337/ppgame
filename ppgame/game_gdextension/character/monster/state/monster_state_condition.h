#ifndef MONSTER_STATE_CONDITION_H
#define MONSTER_STATE_CONDITION_H

#include <godot_cpp/variant/vector2.hpp>
using namespace godot;

#include "fsm/state_condition.h"

struct MonsterStateCondition : StateCondition {
	Vector2 velocity; //!< 速度
	Vector2 global_position; //!< 全局位置
};

#endif // MONSTER_STATE_CONDITION_H
