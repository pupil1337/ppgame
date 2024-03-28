#include "register_types.h"

#include <gdextension_interface.h>
#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/core/defs.hpp>
#include <godot_cpp/godot.hpp>

#include "fsm/finite_state_machine_component.h"
#include "fsm/state.h"

#include "character/player/fsm/motion/air/player_fall_state.h"
#include "character/player/fsm/motion/air/player_jump_state.h"
#include "character/player/fsm/motion/ground/player_idle_state.h"
#include "character/player/fsm/motion/ground/player_run_state.h"
#include "character/player/fsm/player_finite_state_machine_component.h"
#include "character/player/player.h"
#include "character/player/player_movement_component.h"

void initialize_game_gdextension_types(ModuleInitializationLevel p_level) {
	if (p_level != MODULE_INITIALIZATION_LEVEL_SCENE) {
		return;
	}

	GDREGISTER_ABSTRACT_CLASS(FiniteStateMachineComponent);
	GDREGISTER_ABSTRACT_CLASS(State);

	GDREGISTER_CLASS(Player);
	GDREGISTER_CLASS(PlayerMovementComponent);
	GDREGISTER_CLASS(PlayerFiniteStateMachineComponent);
	GDREGISTER_ABSTRACT_CLASS(PlayerGroundBaseState);
	GDREGISTER_CLASS(PlayerIdleState);
	GDREGISTER_CLASS(PlayerRunState);
	GDREGISTER_ABSTRACT_CLASS(PlayerAirBaseState);
	GDREGISTER_CLASS(PlayerJumpState);
	GDREGISTER_CLASS(PlayerFallState);
}

void uninitialize_game_gdextension_types(ModuleInitializationLevel p_level) {
	if (p_level != MODULE_INITIALIZATION_LEVEL_SCENE) {
		return;
	}
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
