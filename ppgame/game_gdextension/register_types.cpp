#include "register_types.h"

#include <gdextension_interface.h>
#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/core/defs.hpp>
#include <godot_cpp/godot.hpp>

using namespace godot;

// Entry
#include "scene/entry.h"

// Player
#include "scene/player/player.h"
#include "scene/player/movement/playerMovementComponent.h"
#include "scene/player/movement/fsm/playerMovementFSMComponent.h"
#include "scene/player/movement/fsm/ground/playerIdleState.h"
#include "scene/player/movement/fsm/ground/playerRunState.h"
#include "scene/player/movement/fsm/air/playerJumpState.h"
#include "scene/player/movement/fsm/air/playerFallState.h"

// UI
#include "scene/gui/menu/menu_main.h"

// System
#include "system/multiplayerSystem.h"

void initialize_game_gdextension_types(ModuleInitializationLevel p_level) {
	if (p_level != MODULE_INITIALIZATION_LEVEL_SCENE) {
		return;
	}

	// Entry
    ClassDB::register_class<Entry>();

    // Player
    ClassDB::register_class<Player>();
    ClassDB::register_class<PlayerMovementComponent>();
	ClassDB::register_class<FiniteStateMachineComponent>();
	ClassDB::register_class<PlayerMovementFSMComponent>();
	ClassDB::register_class<State>();
	ClassDB::register_class<PlayerMovementStateBase>();
	ClassDB::register_class<PlayerGroundBaseState>();
	ClassDB::register_class<PlayerIdleState>();
	ClassDB::register_class<PlayerRunState>();
	ClassDB::register_class<PlayerAirBaseState>();
	ClassDB::register_class<PlayerJumpState>();
	ClassDB::register_class<PlayerFallState>();

	// UI
	ClassDB::register_class<MenuMain>();

    // System
    ClassDB::register_class<MultiplayerSystem>();
}

void uninitialize_game_gdextension_types(ModuleInitializationLevel p_level) {
	if (p_level != MODULE_INITIALIZATION_LEVEL_SCENE) {
		return;
	}
}

extern "C" {
	// Initialization
	GDExtensionBool GDE_EXPORT game_gdextension_library_init(GDExtensionInterfaceGetProcAddress p_get_proc_address, GDExtensionClassLibraryPtr p_library, GDExtensionInitialization *r_initialization) {
		GDExtensionBinding::InitObject init_obj(p_get_proc_address, p_library, r_initialization);
		init_obj.register_initializer(initialize_game_gdextension_types);
		init_obj.register_terminator(uninitialize_game_gdextension_types);
		init_obj.set_minimum_library_initialization_level(MODULE_INITIALIZATION_LEVEL_SCENE);

		return init_obj.init();
	}
}
