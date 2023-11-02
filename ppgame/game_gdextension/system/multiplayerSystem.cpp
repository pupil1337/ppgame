#include "multiplayerSystem.h"

MultiplayerSystem* MultiplayerSystem::singleton = nullptr;

void MultiplayerSystem::_bind_methods() {
	ClassDB::bind_method(D_METHOD(_STR(rpc_hello), "uid"), &self_type::rpc_hello);
}

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
	PP_CONTINUE_IF_GAME
	peer.instantiate();

	Ref<MultiplayerAPI> multiplayerAPI = get_multiplayer();
	ERR_FAIL_COND_EDMSG(multiplayerAPI.is_null(), "MultiplayerAPI 为空");
	multiplayerAPI->connect("peer_connected", callable_mp(this, &MultiplayerSystem::_peer_connected));
	multiplayerAPI->connect("peer_disconnected", callable_mp(this, &MultiplayerSystem::_peer_disconnected));
	multiplayerAPI->connect("connected_to_server", callable_mp(this, &MultiplayerSystem::_connected_to_server));
	multiplayerAPI->connect("connection_failed", callable_mp(this, &MultiplayerSystem::_connection_failed));
	multiplayerAPI->connect("server_disconnected", callable_mp(this, &MultiplayerSystem::_server_disconnected));
}

void MultiplayerSystem::_ready() {
	Dictionary opts;
	opts["rpc_mode"] = MultiplayerAPI::RPC_MODE_ANY_PEER;
	opts["transfer_mode"] = MultiplayerPeer::TRANSFER_MODE_RELIABLE;
	opts["call_local"] = true;
	opts["channel"] = 0;
	rpc_config(_STR(rpc_hello), opts);
}

void MultiplayerSystem::hostGame() {
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

void MultiplayerSystem::joinGame() {
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
	UtilityFunctions::print("join success");
}

void MultiplayerSystem::_peer_connected(int id) {
	UtilityFunctions::print("_peer_connected:: id:" + itos(id));
}

void MultiplayerSystem::_peer_disconnected(int id) {
	UtilityFunctions::print("_peer_disconnected:: id:" + itos(id));
}

void MultiplayerSystem::_connected_to_server() {
	UtilityFunctions::print("_connected_to_server");
	rpc(_STR(rpc_hello), peer->get_unique_id());
}

void MultiplayerSystem::_connection_failed() {
	UtilityFunctions::print("_connection_failed");
}

void MultiplayerSystem::_server_disconnected() {
	UtilityFunctions::print("_server_disconnected");
}

void MultiplayerSystem::rpc_hello(int32_t uid) {
	UtilityFunctions::print(itos(uid) + " say: hello!");
}
