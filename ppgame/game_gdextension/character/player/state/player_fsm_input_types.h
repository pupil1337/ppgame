#ifndef PLAYER_FSM_INPUT_TYPES_H
#define PLAYER_FSM_INPUT_TYPES_H

enum class PlayerFSMInput {
	Reset_Movement_To_Idle, // 重置移动到Idle nullptr
	Animation_Finished, // 动画播放结束 FStringName anim_name
	To_Movement_None_State, // 到移动None状态 int count
	To_Weapon_None_State, // 到武器None状态 int count
	Ban_Movement_Enter_Anim, // 禁用进入移动时播放动画 int count
	Ban_Movement_Input, // 禁用移动输入 int count
	Body_Enter_Melee_Attack, // 实体进入近战攻击区域 Node2D* body
	Body_Exit_Melee_Attack, // 实体退出近战攻击区域 Node2D* body
};

#endif // PLAYER_FSM_INPUT_TYPES_H
