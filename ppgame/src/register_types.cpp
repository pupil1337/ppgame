#include "register_types.h"

#include <core/object/class_db.h>

// Player
#include "player/player.h"
#include "player/movement/playerMovementComponent.h"
#include "player/movement/fsm/playerMovementFSMComponent.h"

void initialize_src_module(ModuleInitializationLevel p_level) {
    if (p_level != MODULE_INITIALIZATION_LEVEL_SCENE) {
            return;
    }

    // Player
    ClassDB::register_class<Player>();
    ClassDB::register_class<PlayerMovementComponent>();
	ClassDB::register_class<PlayerMovementFSMComponent>();
}

void uninitialize_src_module(ModuleInitializationLevel p_level) {
    if (p_level != MODULE_INITIALIZATION_LEVEL_SCENE) {
            return;
    }
}
