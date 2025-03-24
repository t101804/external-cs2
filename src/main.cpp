#include <thread>
#include <cstdlib> 
#include "Game/Cs2/game.h"
#include "Window/overlay.h"

Cs2* cs2 = new Cs2;
Overlay* overlay = new Overlay;


void renderOverlay(Overlay* overlay) {
	while (true) {
		std::this_thread::sleep_for(std::chrono::milliseconds(5));
		overlay->OverlayLoop();
	
	}
}

void cleanup() {
	if (overlay) {
		overlay->DestroyOverlay();
		delete overlay;
		Logging::info_print("Overlay destroyed and resources cleaned up.");
	}
}

int main() {
	//std::atexit(cleanup);
	//cleanup();

	std::thread([&]() { cs2->Start(); }).detach();
	Logging::info_print("Starting Cheat at 3 seconds");
	std::this_thread::sleep_for(std::chrono::seconds(2));
	if (!overlay->InitOverlay(L"NVIDIA GeForce Overlay", WINDOW_TITLE)) {
		Logging::error_print("cant initializing and injecting the overlay");
		return -1;
	}

	std::thread init(renderOverlay, overlay);
	init.join();

	Logging::info_print("good bye");
	// idk why its not work
	cleanup();
	return 0;
}