#include "register_types.h"

#include <core/object/class_db.h>

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

void initialize_src_module(ModuleInitializationLevel p_level) {
    if (p_level != MODULE_INITIALIZATION_LEVEL_SCENE) {
            return;
    }

    // Entry
    ClassDB::register_class<Entry>();

    // Player
    ClassDB::register_class<Player>();
    ClassDB::register_class<PlayerMovementComponent>();
	ClassDB::register_class<PlayerMovementFSMComponent>();
	ClassDB::register_class<PlayerIdleState>();
	ClassDB::register_class<PlayerRunState>();
	ClassDB::register_class<PlayerJumpState>();
	ClassDB::register_class<PlayerFallState>();

	// UI
	ClassDB::register_class<MenuMain>();

    // System
    ClassDB::register_class<MultiplayerSystem>();
}

void uninitialize_src_module(ModuleInitializationLevel p_level) {
    if (p_level != MODULE_INITIALIZATION_LEVEL_SCENE) {
            return;
    }
}
