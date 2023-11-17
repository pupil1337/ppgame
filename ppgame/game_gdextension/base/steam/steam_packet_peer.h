#ifndef STEAM_PACKET_PEER_H
#define STEAM_PACKET_PEER_H

#ifdef _MSC_VER
#pragma warning(disable : 4828)
#endif

using namespace godot;

#include <steam/steam_api.h>

#define MAX_STEAM_PACKET_SIZE k_cbMaxSteamNetworkingSocketsMessageSizeSend

class SteamPacketPeer : public RefCounted {
	GDCLASS(SteamPacketPeer, RefCounted)

protected:
	static void _bind_methods() {}

public:
	SteamPacketPeer() {}
	SteamPacketPeer(const void* p_buffer, uint32_t p_buffer_size, int transferMode);

	// ------------------------------------------

public:
	uint8_t data[MAX_STEAM_PACKET_SIZE];
	uint32_t size = 0;
	uint64_t sender;
	int transfer_mode = k_nSteamNetworkingSend_Reliable; // Looks like a spot that might be served by an enum, eventually.
};
#endif // STEAM_PACKET_PEER_H
