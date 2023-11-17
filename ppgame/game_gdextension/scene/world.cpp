#include "world.h"

#include "scene/player/player.h"
#include "system/multiplayerSystem.h"

void World::_enter_tree() {
	PP_CONTINUE_IF_GAME

	if (MultiplayerSystem::is_server()) {
		MultiplayerSystem::connect("peer_connected", callable_mp(this, &World::_add_player));
		MultiplayerSystem::connect("peer_disconnected", callable_mp(this, &World::_del_player));
	}
}

void World::_ready() {
	PP_CONTINUE_IF_GAME

	if (MultiplayerSystem::is_server()) {
		_add_player(1);
	}
}

void World::_exit_tree() {
	PP_CONTINUE_IF_GAME

	if (MultiplayerSystem::is_server()) {
		MultiplayerSystem::disconnect("peer_connected", callable_mp(this, &World::_add_player));
		MultiplayerSystem::disconnect("peer_disconnected", callable_mp(this, &World::_del_player));
	}
}

void World::_add_player(int32_t uid) {
	ERR_FAIL_COND(players.has(uid));

	UtilityFunctions::print("add player uid:" + itos(uid));

	Ref<PackedScene> player_packed_scene = ResourceLoader::get_singleton()->load("res://scene/player/player.tscn", "PackedScene");
	ERR_FAIL_NULL_EDMSG(player_packed_scene.ptr(), "player PackedScene path is wrong!");
	Player* player = cast_to<Player>(player_packed_scene.ptr()->instantiate());
	ERR_FAIL_NULL(player);
	player->set_uid(uid);
	player->set_name("player" + itos(uid));
	add_child(player, true);

	players.insert(uid, player);
}

void World::_del_player(int32_t uid) {
	ERR_FAIL_COND(!players.has(uid));

	remove_child(players.get(uid));
	players.erase(uid);
}
