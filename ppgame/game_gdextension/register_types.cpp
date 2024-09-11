#include "register_types.h"

#include <gdextension_interface.h>
#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/core/defs.hpp>
#include <godot_cpp/godot.hpp>

#include "async_loader/async_loader.h"
#include "async_loader/scene_instancer.h"
#include "async_loader/scene_loader.h"
#include "character/character.h"
#include "character/character_movement_component.h"
#include "character/monster/monster.h"
#include "character/monster/monster_concurrent_state_machine_component.h"
#include "character/monster/state/behavior/monster_behavior_finite_state_machine_component.h"
#include "character/monster/state/behavior/monster_behavior_none_state.h"
#include "character/monster/state/behavior/monster_chase_state.h"
#include "character/monster/state/behavior/monster_patrol_state.h"
#include "character/monster/state/monster_state.h"
#include "character/player/player.h"
#include "character/player/player_camera_component.h"
#include "character/player/player_concurrent_state_machine_component.h"
#include "character/player/player_input_component.h"
#include "character/player/state/movement/air/player_air_fall_state.h"
#include "character/player/state/movement/air/player_air_jump_state.h"
#include "character/player/state/movement/air/player_air_state.h"
#include "character/player/state/movement/ground/player_ground_idle_state.h"
#include "character/player/state/movement/ground/player_ground_run_state.h"
#include "character/player/state/movement/ground/player_ground_state.h"
#include "character/player/state/movement/player_movement_finite_state_machine_component.h"
#include "character/player/state/movement/player_movement_none_state.h"
#include "character/player/state/player_state.h"
#include "character/player/state/weapon/player_weapon_finite_state_machine_component.h"
#include "character/player/state/weapon/player_weapon_none_state.h"
#include "character/player/state/weapon/sword/player_sword_attack.h"
#include "framework/component.h"
#include "fsm/concurrent_state_machine_component.h"
#include "fsm/finite_state_machine_component.h"
#include "fsm/state.h"
#include "gm/gm.h"
#include "level/door.h"
#include "level/level.h"
#include "utils/debug_draw_utils.h"
#include "utils/debug_test_node.h"
#include "utils/input_string_names.h"
#include "world/world.h"

void initialize_game_gdextension_types(ModuleInitializationLevel p_level) {
	if (p_level != MODULE_INITIALIZATION_LEVEL_SCENE) {
		return;
	}

	InputStringNames::create();

	// framework
	GDREGISTER_ABSTRACT_CLASS(Component)

	// fsm
	GDREGISTER_ABSTRACT_CLASS(FiniteStateMachineComponent)
	GDREGISTER_ABSTRACT_CLASS(State)
	GDREGISTER_ABSTRACT_CLASS(ConcurrentStateMachineComponent)

	// character
	GDREGISTER_CLASS(Character)
	GDREGISTER_CLASS(CharacterMovementComponent)

	// player
	GDREGISTER_CLASS(Player)
	GDREGISTER_CLASS(PlayerInputComponent)
	GDREGISTER_CLASS(PlayerCameraComponent)
	GDREGISTER_CLASS(PlayerConcurrentStateMachineComponent)
	GDREGISTER_ABSTRACT_CLASS(PlayerState)
	GDREGISTER_CLASS(PlayerMovementFiniteStateMachineComponent)
	GDREGISTER_CLASS(PlayerMovementNoneState)
	GDREGISTER_ABSTRACT_CLASS(PlayerGroundState)
	GDREGISTER_CLASS(PlayerGroundIdleState)
	GDREGISTER_CLASS(PlayerGroundRunState)
	GDREGISTER_ABSTRACT_CLASS(PlayerAirState)
	GDREGISTER_CLASS(PlayerAirJumpState)
	GDREGISTER_CLASS(PlayerAirFallState)
	GDREGISTER_CLASS(PlayerWeaponFiniteStateMachineComponent)
	GDREGISTER_CLASS(PlayerWeaponNoneState)
	GDREGISTER_CLASS(PlayerSwordAttack)

	// monster
	GDREGISTER_CLASS(Monster)
	GDREGISTER_CLASS(MonsterConcurrentStateMachineComponent)
	GDREGISTER_ABSTRACT_CLASS(MonsterState)
	GDREGISTER_CLASS(MonsterBehaviorFiniteStateMachineComponent)
	GDREGISTER_CLASS(MonsterBehaviorNoneState)
	GDREGISTER_CLASS(MonsterPatrolState)
	GDREGISTER_CLASS(MonsterChaseState)

	// world
	GDREGISTER_CLASS(World)

	// level
	GDREGISTER_CLASS(Level)
	GDREGISTER_CLASS(Door)

	// async_loader
	GDREGISTER_CLASS(AsyncLoader)
	GDREGISTER_CLASS(SceneLoader)
	GDREGISTER_CLASS(SceneInstancer)

	// gm
	GDREGISTER_CLASS(GM)

	// utils
	GDREGISTER_CLASS(DebugDrawUtils)
	GDREGISTER_CLASS(DebugTestNode)
}

void uninitialize_game_gdextension_types(ModuleInitializationLevel p_level) {
	if (p_level != MODULE_INITIALIZATION_LEVEL_SCENE) {
		return;
	}

	InputStringNames::free();
}

extern "C" {
// Initialization
GDExtensionBool GDE_EXPORT game_gdextension_library_init(GDExtensionInterfaceGetProcAddress p_get_proc_address, GDExtensionClassLibraryPtr p_library, GDExtensionInitialization* r_initialization) {
	GDExtensionBinding::InitObject init_obj(p_get_proc_address, p_library, r_initialization);
	init_obj.register_initializer(initialize_game_gdextension_types);
	init_obj.register_terminator(uninitialize_game_gdextension_types);
	init_obj.set_minimum_library_initialization_level(MODULE_INITIALIZATION_LEVEL_SCENE);

	return init_obj.init();
}
}
