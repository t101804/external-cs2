#include <thread>
#include "Game/Cs2/game.h"
#include "Window/overlay.h"

// Cs2* cs2 = new Cs2;
Overlay* overlay = new Overlay;

//overlay->OverlayLoop();
//overlay->DestroyOverlay();
//delete overlay;
int main() {
	if (!overlay->InitOverlay(L"NVIDIA GeForce Overlay", WINDOW_TITLE)) {
		Logging::error_print("cant initializing and injecting the overlay");
	}
	overlay->OverlayLoop();

	Logging::debug_print("destroying overlay");
	overlay->DestroyOverlay();
	delete overlay;
	/*overlay->DestroyOverlay();*/
	/*cs2->Start();*/
	/*Sleep(3000);*/
	//if (!fivem->Overlay()) {
	//	Logging::error_print("cant initializing and injecting the overlay");
	//}
	//delete cs2;
	return 0;
}