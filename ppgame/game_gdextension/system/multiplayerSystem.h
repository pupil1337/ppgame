#ifndef MULTIPLAYERSYSTEM_H
#define MULTIPLAYERSYSTEM_H

using namespace godot;

class MultiplayerSystem : public Node {
	GDCLASS(MultiplayerSystem, Node);

	static MultiplayerSystem* singleton;

public:
	MultiplayerSystem();
	~MultiplayerSystem();

protected:
	static void _bind_methods() {}

public:
	virtual void _enter_tree() override;
	virtual void _exit_tree() override;

	// ------------------------------------------

	// Matchmaking
	CCallResult<MultiplayerSystem, LobbyCreated_t> callResultCreateLobby;
	void lobby_created(LobbyCreated_t* call_data, bool io_failure);
	CCallResult<MultiplayerSystem, LobbyMatchList_t> callResultLobbyList;
	void lobby_match_list(LobbyMatchList_t* call_data, bool io_failure);

public:
	void create_lobby();

	static void hostGame();
	static void joinGame();

	static void connect(const StringName& signal, const Callable& callable, uint32_t flags = 0U);
	static void disconnect(const StringName& signal, const Callable& callable);

	static int32_t get_unique_id();
	static bool is_server();

private:
	static Ref<MultiplayerAPI> _get_multiplayer();
};

#endif // MULTIPLAYERSYSTEM_H
