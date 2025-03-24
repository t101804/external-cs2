#include "game.h"
#include "../globals.hpp"
#include "../../Utils/Math/math.h"
#include "Features/Visuals/visual.h"

uintptr_t Cs2::client_dll;
uintptr_t Cs2::server_dll;


void Cs2::Start() {

	Logging::info_print("meowdiocre");
	if (!DetectGame()) {
		Logging::error_print("cant detect the game");
		return;
	}
	if (!Setup()) {
		Logging::error_print("cant setup globals cache");
		return;
	}
	Logging::info_print("game initated started succesfully");

	// caching the entity
	Globals::CacheEntity();
}


void Cs2::RenderEntity() {
	Visuals visuals;
	for (auto& entity : Globals::EntityList) {
		Entity* pEntity = &entity;

		visuals.Render(pEntity);
	}
}
