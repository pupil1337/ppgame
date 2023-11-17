#ifndef STEAM_CONNECTION_H
#define STEAM_CONNECTION_H

using namespace godot;

#include <steam/steamnetworkingtypes.h>

#include "steam_packet_peer.h"

#define MAX_STEAM_PACKET_SIZE k_cbMaxSteamNetworkingSocketsMessageSizeSend

class SteamConnection : public RefCounted {
	GDCLASS(SteamConnection, RefCounted)

protected:
	static void _bind_methods() {}

public:
	SteamConnection() {}
	SteamConnection(uint64_t steam_id);
	~SteamConnection();
	bool operator==(const SteamConnection& data);

	// ------------------------------------------

public:
	struct SetupPeerPayload {
		uint32_t peer_id = -1;
	};
	bool m_bActive; // Is this slot in use? Or is it available for new connections?
	uint64_t steam_id; // What is the steamid of the player?
	HSteamNetConnection steam_connection; // The handle for the connection to the player
	uint64 m_ulTickCountLastData; // What was the last time we got data from the player?
	int peer_id;
	uint64_t last_msg_timestamp;
	List<Ref<SteamPacketPeer>> pending_retry_packets;

private:
	EResult _raw_send(Ref<SteamPacketPeer> packet);
	String _convert_eresult_to_string(EResult e);
	Error _send_pending();
	void _add_packet(Ref<SteamPacketPeer> packet);
	Error _send_setup_peer(const SetupPeerPayload payload);

public:
	// REVIEW Enetpeer contains broadcast method (Research for method in steam sockets)
	// void broadcast(enet_uint8 p_channel, ENetPacket *p_packet);
	Error send(Ref<SteamPacketPeer> packet);
	void flush();
	bool close();

	Error request_peer();
	Error send_peer(uint32_t peer_id);
};

#endif // STEAM_CONNECTION_H
