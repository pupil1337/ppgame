#ifndef MULTIPLAYERSYSTEM_H
#define MULTIPLAYERSYSTEM_H

using namespace godot;

class MultiplayerSystem : public Node {
	GDCLASS(MultiplayerSystem, Node);

protected:
	static void _bind_methods();

	static MultiplayerSystem* singleton;

public:
	MultiplayerSystem();
	~MultiplayerSystem();
	static MultiplayerSystem* get_singleton();

public:
	virtual void _enter_tree() override;
	virtual void _ready() override;

//~Begin This Class
public:
	void hostGame();
	void joinGame();

private:
	void _peer_connected(int id);
	void _peer_disconnected(int id);
	void _connected_to_server();
	void _connection_failed();
	void _server_disconnected();

public:
	void rpc_hello(int32_t uid);

	Ref<ENetMultiplayerPeer> peer;
	Vector<int32_t> player_uids;
};

#endif // MULTIPLAYERSYSTEM_H
