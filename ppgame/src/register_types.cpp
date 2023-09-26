#include "register_types.h"

#include <core/object/class_db.h>

#include "player/player.h"
#include "finiteStateMachine/finiteStateMachine.h"

void initialize_src_module(ModuleInitializationLevel p_level) {
    if (p_level != MODULE_INITIALIZATION_LEVEL_SCENE) {
            return;
    }
    ClassDB::register_class<Player>();
    ClassDB::register_class<FiniteStateMachine>();
}

void uninitialize_src_module(ModuleInitializationLevel p_level) {
    if (p_level != MODULE_INITIALIZATION_LEVEL_SCENE) {
            return;
    }
}