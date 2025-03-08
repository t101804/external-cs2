#include "game.h"
#include "../globals.hpp"

uintptr_t Cs2::client_dll;
uintptr_t Cs2::server_dll;


void Cs2::Start() {

	Logging::debug_print("starting cheetoz sir, tobi gtg bgt");
	if (!DetectGame()) {
		Logging::error_print("cant detect the game");
		return;
	}
	if (!Setup()) {
		// exiting a application
		Logging::error_print("cant setup globals cache");
		return;
	}
	Logging::info_print("game initated started succesfully");

	 Globals::EntityRenderUpdate();
}