#ifndef STEAM_MULTIPLAYER_PEER_H
#define STEAM_MULTIPLAYER_PEER_H

using namespace godot;

class SteamMultiplayerPeer : public MultiplayerPeerExtension {
	GDCLASS(SteamMultiplayerPeer, MultiplayerPeerExtension)

protected:
	static void _bind_methods() {}

	// ------------------------------------------

public:
	virtual Error _get_packet(const uint8_t** r_buffer, int32_t* r_buffer_size) override;
	virtual Error _put_packet(const uint8_t* p_buffer, int32_t p_buffer_size) override;
	virtual int32_t _get_available_packet_count() const override;
	virtual int32_t _get_max_packet_size() const override;
	virtual PackedByteArray _get_packet_script() override;
	virtual Error _put_packet_script(const PackedByteArray& p_buffer) override;
	virtual int32_t _get_packet_channel() const override;
	virtual MultiplayerPeer::TransferMode _get_packet_mode() const override;
	virtual void _set_transfer_channel(int32_t p_channel) override;
	virtual int32_t _get_transfer_channel() const override;
	virtual void _set_transfer_mode(MultiplayerPeer::TransferMode p_mode) override;
	virtual MultiplayerPeer::TransferMode _get_transfer_mode() const override;
	virtual void _set_target_peer(int32_t p_peer) override;
	virtual int32_t _get_packet_peer() const override;
	virtual bool _is_server() const override;
	virtual void _poll() override;
	virtual void _close() override;
	virtual void _disconnect_peer(int32_t p_peer, bool p_force) override;
	virtual int32_t _get_unique_id() const override;
	virtual void _set_refuse_new_connections(bool p_enable) override;
	virtual bool _is_refusing_new_connections() const override;
	virtual bool _is_server_relay_supported() const override;
	virtual MultiplayerPeer::ConnectionStatus _get_connection_status() const override;
};

#endif // STEAM_MULTIPLAYER_PEER_H
