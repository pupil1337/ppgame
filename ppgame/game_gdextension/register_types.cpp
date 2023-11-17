#include "register_types.h"

using namespace godot;

// Base
#include "base/finiteStateMachine/finiteStateMachineComponent.h"
#include "base/finiteStateMachine/state.h"

// Game
#include "scene/game.h"
#include "scene/world.h"

// Player
#include "scene/player/movement/fsm/air/playerFallState.h"
#include "scene/player/movement/fsm/air/playerJumpState.h"
#include "scene/player/movement/fsm/ground/playerIdleState.h"
#include "scene/player/movement/fsm/ground/playerRunState.h"
#include "scene/player/movement/fsm/playerMovementFSMComponent.h"
#include "scene/player/movement/playerMovementComponent.h"
#include "scene/player/player.h"
#include "scene/player/playerControllerComponent.h"

// UI
#include "scene/gui/menu/menu_main.h"

// System
#include "base/steam/steam_connection.h"
#include "base/steam/steam_multiplayer_peer.h"
#include "base/steam/steam_packet_peer.h"
#include "system/multiplayerSystem.h"

void initialize_game_gdextension_types(ModuleInitializationLevel p_level) {
	if (p_level != MODULE_INITIALIZATION_LEVEL_SCENE) {
		return;
	}

	// Base
	ClassDB::register_class<FiniteStateMachineComponent>();
	ClassDB::register_class<State>();

	// Game
	ClassDB::register_class<Game>();
	ClassDB::register_class<World>();

	// Player
	ClassDB::register_class<Player>();
	ClassDB::register_class<PlayerMovementComponent>();
	ClassDB::register_class<PlayerMovementFSMComponent>();
	ClassDB::register_class<PlayerMovementStateBase>();
	ClassDB::register_class<PlayerGroundBaseState>();
	ClassDB::register_class<PlayerIdleState>();
	ClassDB::register_class<PlayerRunState>();
	ClassDB::register_class<PlayerAirBaseState>();
	ClassDB::register_class<PlayerJumpState>();
	ClassDB::register_class<PlayerFallState>();
	ClassDB::register_class<PlayerControllerComponent>();

	// UI
	ClassDB::register_class<MenuMain>();

	// System
	ClassDB::register_class<MultiplayerSystem>();
	ClassDB::register_class<SteamPacketPeer>();
	ClassDB::register_class<SteamConnection>();
	ClassDB::register_class<SteamMultiplayerPeer>();
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
