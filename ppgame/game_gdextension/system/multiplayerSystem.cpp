#include "multiplayerSystem.h"

#include "base/steam/steam_multiplayer_peer.h"

MultiplayerSystem* MultiplayerSystem::singleton = nullptr;

MultiplayerSystem::MultiplayerSystem() {
	singleton = this;
}

MultiplayerSystem::~MultiplayerSystem() {
	singleton = nullptr;
}

MultiplayerSystem* MultiplayerSystem::get_singleton() {
	return singleton;
}

// ----------------------------------------------------------------------------

void MultiplayerSystem::_enter_tree() {
	PP_CONTINUE_IF_GAME

	SteamAPI_RestartAppIfNecessary(2113080);
	SteamAPI_Init();

	SteamNetworkingUtils()->InitRelayNetworkAccess();
}

void MultiplayerSystem::_process(double delta) {
	SteamAPI_RunCallbacks();
}

void MultiplayerSystem::_exit_tree() {
	PP_CONTINUE_IF_GAME

	SteamAPI_Shutdown();
}

void MultiplayerSystem::lobby_created(LobbyCreated_t* call_data, bool io_failure) {
	ERR_FAIL_COND(io_failure);

	CSteamID lobby_id = call_data->m_ulSteamIDLobby;
	uint64_t lobby = lobby_id.ConvertToUint64();
	UtilityFunctions::print("Create Lobby Success! lobby id: " + uitos(lobby));

	Ref<SteamMultiplayerPeer> peer;
	peer.instantiate();

	Error err = peer->create_host(0, {});
	UtilityFunctions::print("create_host err?(0:OK): " + itos(err));
	_get_multiplayer()->set_multiplayer_peer(peer);
}

void MultiplayerSystem::lobby_match_list(LobbyMatchList_t* call_data, bool io_failure) {
	ERR_FAIL_COND(io_failure);

	int lobby_count = call_data->m_nLobbiesMatching;
	for (int i = 0; i < lobby_count; ++i) {
		CSteamID lobby_id = SteamMatchmaking()->GetLobbyByIndex(i);
		uint64_t lobby = lobby_id.ConvertToUint64();
		UtilityFunctions::print("Find Lobby id: " + uitos(lobby));

		if (i == 0) {
			SteamAPICall_t api_call = SteamMatchmaking()->JoinLobby(lobby_id);
			callResultJoinLobby.Set(api_call, this, &MultiplayerSystem::lobby_enter);
		}
	}
}

void MultiplayerSystem::lobby_enter(LobbyEnter_t* call_data, bool io_failure) {
	ERR_FAIL_COND(io_failure);

	UtilityFunctions::print("Lobby Enter");

	CSteamID id = SteamMatchmaking()->GetLobbyOwner(call_data->m_ulSteamIDLobby);

	Ref<SteamMultiplayerPeer> peer;
	peer.instantiate();

	Error err = peer.ptr()->create_client(id.ConvertToUint64(), 0, {});
	UtilityFunctions::print("create_client err?(0:OK): " + itos(err));

	_get_multiplayer()->set_multiplayer_peer(peer);
}

void MultiplayerSystem::create_lobby() {
	if (SteamMatchmaking() != nullptr) {
		SteamAPICall_t api_call = SteamMatchmaking()->CreateLobby(ELobbyType::k_ELobbyTypePublic, 8);
		callResultCreateLobby.Set(api_call, this, &MultiplayerSystem::lobby_created);
	}
}

void MultiplayerSystem::request_lobby_list() {
	if (SteamMatchmaking() != nullptr) {
		SteamAPICall_t api_call = SteamMatchmaking()->RequestLobbyList();
		callResultLobbyList.Set(api_call, this, &MultiplayerSystem::lobby_match_list);
	}
}

void MultiplayerSystem::hostGame() {
	create_lobby();
}

void MultiplayerSystem::joinGame() {
	request_lobby_list();
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
