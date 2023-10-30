#include "multiplayerSystem.h"

MultiplayerSystem* MultiplayerSystem::singleton = nullptr;

MultiplayerSystem::MultiplayerSystem() {
	singleton = this;

	// todo
}

MultiplayerSystem::~MultiplayerSystem() {
	singleton = nullptr;
}

MultiplayerSystem *MultiplayerSystem::get_singleton() {
	return singleton;
}

