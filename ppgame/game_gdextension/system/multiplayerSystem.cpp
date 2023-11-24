#include "multiplayerSystem.h"

#include "base/steam/steam_multiplayer_peer.h"

MultiplayerSystem* MultiplayerSystem::singleton = nullptr;

MultiplayerSystem::MultiplayerSystem()
// :callbackRelayNetworkStatus(this, &self_type::relay_network_status)
{
	singleton = this;
}

MultiplayerSystem::~MultiplayerSystem() {
	singleton = nullptr;
}

MultiplayerSystem* MultiplayerSystem::get_singleton() {
	return singleton;
}

void MultiplayerSystem::_bind_methods() {
	ClassDB::bind_method(D_METHOD("get_steam_networking_availability"), &self_type::_get_steam_networking_availability);
}

// ----------------------------------------------------------------------------

extern "C" void __cdecl SteamAPIDebugTextHook(int nSeverity, const char* pchDebugText) {
	UtilityFunctions::print(pchDebugText);
}

void MultiplayerSystem::_enter_tree() {
	PP_CONTINUE_IF_GAME

	if (SteamAPI_RestartAppIfNecessary(2113080)) {
		OS::get_singleton()->alert(
				"Not run by Steam! will run it then start game.\n"
				"https://partner.steamgames.com/doc/api/steam_api#SteamAPI_RestartAppIfNecessary",
				"SteamAPI_RestartAppIfNecessary()");
		get_tree()->quit();
		return;
	}

	if (!SteamAPI_Init()) {
		OS::get_singleton()->alert(
				"Steam Not Running?\n"
				"https://partner.steamgames.com/doc/api/steam_api#SteamAPI_Init",
				"!SteamAPI_Init()");
		get_tree()->quit();
		return;
	}

	SteamUtils()->SetWarningMessageHook(&SteamAPIDebugTextHook);

	SteamNetworkingUtils()->InitRelayNetworkAccess();
}

void MultiplayerSystem::_process(double delta) {
	PP_CONTINUE_IF_GAME

	SteamAPI_RunCallbacks();
}

// void MultiplayerSystem::relay_network_status(SteamRelayNetworkStatus_t* call_data) {
// 	UtilityFunctions::print("relay_network_status: " + _get_steam_networking_availability_name(call_data->m_eAvail));
// }

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

ESteamNetworkingAvailability MultiplayerSystem::_get_steam_networking_availability() const {
	if (SteamNetworkingUtils() == nullptr) {
		return ESteamNetworkingAvailability::k_ESteamNetworkingAvailability_Unknown;
	}
	return SteamNetworkingUtils()->GetRelayNetworkStatus(nullptr);
}

String MultiplayerSystem::_get_steam_networking_availability_name(ESteamNetworkingAvailability type) const {
	switch (type) {
		case k_ESteamNetworkingAvailability_CannotTry:
			return "CannotTry";
		case k_ESteamNetworkingAvailability_Failed:
			return "Failed";
		case k_ESteamNetworkingAvailability_Previously:
			return "Previously";
		case k_ESteamNetworkingAvailability_Retrying:
			return "Retrying";
		case k_ESteamNetworkingAvailability_NeverTried:
			return "NeverTried";
		case k_ESteamNetworkingAvailability_Waiting:
			return "Waiting";
		case k_ESteamNetworkingAvailability_Attempting:
			return "Attempting";
		case k_ESteamNetworkingAvailability_Current:
			return "Current";
		case k_ESteamNetworkingAvailability_Unknown:
			return "Unknown";
		case k_ESteamNetworkingAvailability__Force32bit:
			return "Force32bit";
	}
	return "Not this type";
}
