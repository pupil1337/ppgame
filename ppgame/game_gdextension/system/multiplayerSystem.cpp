#include "multiplayerSystem.h"

MultiplayerSystem* MultiplayerSystem::singleton = nullptr;

MultiplayerSystem::MultiplayerSystem() {
    singleton = this;
}

MultiplayerSystem::~MultiplayerSystem() {
	singleton = nullptr;
}

MultiplayerSystem *MultiplayerSystem::get_singleton() {
	return singleton;
}

void MultiplayerSystem::_enter_tree() {
	PP_CONTINUE_IF_GAME
	peer.instantiate();
}

void MultiplayerSystem::hostGame() {
	ERR_FAIL_NULL(peer.ptr());
	Error error = peer.ptr()->create_server(9527); // TODO
	ERR_FAIL_COND_EDMSG(error != Error::OK, "peer->create_server error:" + error);

	Ref<ENetConnection> host = peer->get_host();
	ERR_FAIL_NULL(host.ptr());
	host.ptr()->compress(ENetConnection::CompressionMode::COMPRESS_RANGE_CODER);
	Ref<MultiplayerAPI> multiplayerAPI = get_multiplayer();
	ERR_FAIL_NULL(multiplayerAPI.ptr());
	multiplayerAPI->set_multiplayer_peer(peer);
	UtilityFunctions::print("host success!");
}

void MultiplayerSystem::joinGame() {
	ERR_FAIL_NULL(peer.ptr());
	Error error = peer->create_client("127.0.0.1", 9527); // TODO
	ERR_FAIL_COND_EDMSG(error != Error::OK, "peer->create_client error:" + error);

	Ref<ENetConnection> host = peer->get_host();
	ERR_FAIL_NULL(host.ptr());
	host.ptr()->compress(ENetConnection::CompressionMode::COMPRESS_RANGE_CODER);
	Ref<MultiplayerAPI> multiplayerAPI = get_multiplayer();
	ERR_FAIL_NULL(multiplayerAPI.ptr());
	multiplayerAPI->set_multiplayer_peer(peer);
	UtilityFunctions::print("join success");
}
