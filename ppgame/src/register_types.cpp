#include "register_types.h"

#include <core/object/class_db.h>

// Common
#include "finiteStateMachine/finiteStateMachineComponent.h"

// Player
#include "player/player.h"
    // components
#include "player/movement/playerMovementComponent.h"
    // fsm.states
#include "player/fsm/ground/playerIdleState.h"
#include "player/fsm/ground/playerRunState.h"

void initialize_src_module(ModuleInitializationLevel p_level) {
    if (p_level != MODULE_INITIALIZATION_LEVEL_SCENE) {
            return;
    }

    // Common
    ClassDB::register_class<FiniteStateMachineComponent>();

    // Player
    ClassDB::register_class<Player>();
        // components
    ClassDB::register_class<PlayerMovementComponent>();
        // fsm.states
    ClassDB::register_class<PlayerIdleState>();
	ClassDB::register_class<PlayerRunState>();

}

void uninitialize_src_module(ModuleInitializationLevel p_level) {
    if (p_level != MODULE_INITIALIZATION_LEVEL_SCENE) {
            return;
    }
}
