#include "multiplayerSystem.h"

#include "steam/steam_api.h"

MultiplayerSystem* MultiplayerSystem::singleton = nullptr;

MultiplayerSystem::MultiplayerSystem() {
	singleton = this;
}

MultiplayerSystem::~MultiplayerSystem() {
	singleton = nullptr;
}

// ----------------------------------------------------------------------------

void MultiplayerSystem::_enter_tree() {
	PP_CONTINUE_IF_GAME

	SteamAPI_RestartAppIfNecessary(2113080);
	SteamAPI_Init();
}

void MultiplayerSystem::_exit_tree() {
	PP_CONTINUE_IF_GAME

	SteamAPI_Shutdown();
}

void MultiplayerSystem::lobby_created(LobbyCreated_t* call_data, bool io_failure) {
}

void MultiplayerSystem::lobby_match_list(LobbyMatchList_t* call_data, bool io_failure) {
}

void MultiplayerSystem::create_lobby() {
	if (SteamMatchmaking() != nullptr) {
		SteamAPICall_t api_call = SteamMatchmaking()->CreateLobby(ELobbyType::k_ELobbyTypePublic, 4);
		callResultCreateLobby.Set(api_call, this, &MultiplayerSystem::lobby_created);
	}
}

void MultiplayerSystem::hostGame() {
	singleton->create_lobby();
	// Ref<ENetMultiplayerPeer> peer;
	// peer.instantiate();

	// Error error = peer.ptr()->create_server(9527); // TODO
	// ERR_FAIL_COND(error != Error::OK);

	// Ref<ENetConnection> host = peer.ptr()->get_host();
	// ERR_FAIL_NULL(host);
	// host.ptr()->compress(ENetConnection::CompressionMode::COMPRESS_RANGE_CODER);

	// Ref<MultiplayerAPI> multiplayerAPI = _get_multiplayer();
	// ERR_FAIL_NULL(multiplayerAPI);
	// multiplayerAPI.ptr()->set_multiplayer_peer(peer);
	// UtilityFunctions::print("host success!");
}

void MultiplayerSystem::joinGame() {
	Ref<ENetMultiplayerPeer> peer;
	peer.instantiate();

	Error error = peer.ptr()->create_client("127.0.0.1", 9527); // TODO
	ERR_FAIL_COND(error != Error::OK);

	Ref<ENetConnection> host = peer.ptr()->get_host();
	ERR_FAIL_NULL(host);
	host.ptr()->compress(ENetConnection::CompressionMode::COMPRESS_RANGE_CODER);

	Ref<MultiplayerAPI> multiplayerAPI = _get_multiplayer();
	ERR_FAIL_NULL(multiplayerAPI);
	multiplayerAPI.ptr()->set_multiplayer_peer(peer);
	UtilityFunctions::print("join success");
}

void MultiplayerSystem::connect(const StringName& signal, const Callable& callable, uint32_t flags) {
	const Ref<MultiplayerAPI>& multiplayerAPI = _get_multiplayer();
	ERR_FAIL_NULL(multiplayerAPI);
	multiplayerAPI.ptr()->connect(signal, callable, flags);
}

void MultiplayerSystem::disconnect(const StringName& signal, const Callable& callable) {
	const Ref<MultiplayerAPI>& multiplayerAPI = _get_multiplayer();
	ERR_FAIL_NULL(multiplayerAPI);
	multiplayerAPI.ptr()->disconnect(signal, callable);
}

int32_t MultiplayerSystem::get_unique_id() {
	const Ref<MultiplayerAPI>& multiplayerAPI = _get_multiplayer();
	ERR_FAIL_NULL_V(multiplayerAPI, 0);
	return multiplayerAPI.ptr()->get_unique_id();
}

bool MultiplayerSystem::is_server() {
	const Ref<MultiplayerAPI>& multiplayerAPI = _get_multiplayer();
	ERR_FAIL_NULL_V(multiplayerAPI, false);
	return multiplayerAPI.ptr()->is_server();
}

Ref<MultiplayerAPI> MultiplayerSystem::_get_multiplayer() {
	ERR_FAIL_NULL_V(singleton, nullptr);
	return singleton->get_multiplayer();
}
