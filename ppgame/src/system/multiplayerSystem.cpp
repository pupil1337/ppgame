#include "multiplayerSystem.h"

// #include <modules/enet/enet_multiplayer_peer.h>
#include <scene/main/multiplayer_api.h>
#include <scene/main/window.h>
#include <scene/resources/packed_scene.h>

MultiplayerSystem* MultiplayerSystem::singleton = nullptr;

MultiplayerSystem::MultiplayerSystem() {
	singleton = this;
}

MultiplayerSystem::~MultiplayerSystem() {
	singleton = nullptr;
	// peer.unref();? todo
}

MultiplayerSystem *MultiplayerSystem::get_singleton() {
	return singleton;
}

void MultiplayerSystem::_notification(int p_notification) {
	switch (p_notification) {
		case NOTIFICATION_POST_ENTER_TREE: {
			if (!Engine::get_singleton()->is_editor_hint()) {
				_enter_tree();
			}
		} break;
	}
}

void MultiplayerSystem::HostGame() {
	// Ref<PackedScene> Map = ResourceLoader::load("res://scene/level/main.tscn", "PackedScene");
	// if (Map.is_valid()) {
	// 	get_tree()->get_root()->add_child(Map->instantiate());
	// }

	// ERR_FAIL_NULL_EDMSG(peer, "MultiplayerSystem::HostGame peer == nullptr");
	// Error error = peer->create_server(9527);
	// ERR_FAIL_COND_EDMSG(error != Error::OK, "peer->create_server error:" + error);

	// ERR_FAIL_NULL(peer->get_host());
	// peer->get_host()->compress(ENetConnection::CompressionMode::COMPRESS_RANGE_CODER);
	// get_multiplayer()->set_multiplayer_peer(peer);
	// print_line("host success!");
}

void MultiplayerSystem::JoinGame() {
}

void MultiplayerSystem::_enter_tree() {
	// peer.instantiate();
}
