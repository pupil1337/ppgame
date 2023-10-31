#include "multiplayerSystem.h"

#include <godot_cpp/classes/multiplayer_api.hpp>
#include <godot_cpp/classes/e_net_connection.hpp>
#include <godot_cpp/classes/resource_loader.hpp>
#include <godot_cpp/classes/packed_scene.hpp>
#include <godot_cpp/classes/scene_tree.hpp>
#include <godot_cpp/classes/window.hpp>

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

void MultiplayerSystem::_enter_tree() {
	PP_CONTINUE_IF_GAME;
	peer.instantiate();

	Ref<MultiplayerAPI> multiplayerAPI = get_multiplayer();
	ERR_FAIL_COND_EDMSG(multiplayerAPI.is_null(), "MultiplayerAPI 为空");
	multiplayerAPI->connect("peer_connected", callable_mp(this, &MultiplayerSystem::peer_connected));
	multiplayerAPI->connect("peer_disconnected", callable_mp(this, &MultiplayerSystem::peer_disconnected));
	multiplayerAPI->connect("connected_to_server", callable_mp(this, &MultiplayerSystem::connected_to_server));
	multiplayerAPI->connect("connection_failed", callable_mp(this, &MultiplayerSystem::connection_failed));
	multiplayerAPI->connect("server_disconnected", callable_mp(this, &MultiplayerSystem::server_disconnected));
}

void MultiplayerSystem::HostGame() {
	Ref<PackedScene> Map = ResourceLoader::get_singleton()->load("res://scene/level/main.tscn", "PackedScene");
	if (Map.is_valid()) {
		get_tree()->get_root()->add_child(Map->instantiate());
	}

	ERR_FAIL_NULL_EDMSG(peer, "MultiplayerSystem::HostGame peer == nullptr");
	Error error = peer->create_server(9527);
	ERR_FAIL_COND_EDMSG(error != Error::OK, "peer->create_server error:" + error);

	ERR_FAIL_NULL(peer->get_host());
	peer->get_host()->compress(ENetConnection::CompressionMode::COMPRESS_RANGE_CODER);
	get_multiplayer()->set_multiplayer_peer(peer);
	UtilityFunctions::print("host success!");
}

void MultiplayerSystem::JoinGame() {
	Ref<PackedScene> Map = ResourceLoader::get_singleton()->load("res://scene/level/main.tscn", "PackedScene");
	if (Map.is_valid()) {
		get_tree()->get_root()->add_child(Map->instantiate());
	}

	ERR_FAIL_NULL_EDMSG(peer, "MultiplayerSystem::JoinGame peer == nullptr");
	Error error = peer->create_client("127.0.0.1", 9527);
	ERR_FAIL_COND_EDMSG(error != Error::OK, "peer->create_client error:" + error);

	ERR_FAIL_NULL(peer->get_host());
	peer->get_host()->compress(ENetConnection::CompressionMode::COMPRESS_RANGE_CODER);
	get_multiplayer()->set_multiplayer_peer(peer);
	UtilityFunctions::print("host success");
}

void MultiplayerSystem::peer_connected(int id) {
	UtilityFunctions::print("peer_connected:: id:" + itos(id));
}

void MultiplayerSystem::peer_disconnected(int id) {
	UtilityFunctions::print("peer_disconnected:: id:" + itos(id));
}

void MultiplayerSystem::connected_to_server() {
	UtilityFunctions::print("connected_to_server");
}

void MultiplayerSystem::connection_failed() {
	UtilityFunctions::print("connection_failed");
}

void MultiplayerSystem::server_disconnected() {
	UtilityFunctions::print("server_disconnected");
}
