#ifndef MULTIPLAYERSYSTEM_H
#define MULTIPLAYERSYSTEM_H

#include <godot_cpp/classes/node.hpp>
#include <godot_cpp/classes/e_net_multiplayer_peer.hpp>

#include "pp.h"

using namespace godot;

class MultiplayerSystem : public Node {
	GDCLASS(MultiplayerSystem, Node);

	static MultiplayerSystem* singleton;

public:
	MultiplayerSystem();
	~MultiplayerSystem();
	static MultiplayerSystem* get_singleton();

protected:
	static void _bind_methods() {}

public:
	virtual void _enter_tree() override;

//~Begin This Class
public:
	void HostGame();
	void JoinGame();

private:
	void peer_connected(int id);
	void peer_disconnected(int id);
	void connected_to_server();
	void connection_failed();
	void server_disconnected();

	Ref<ENetMultiplayerPeer> peer;
};

#endif // MULTIPLAYERSYSTEM_H
