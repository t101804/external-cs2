#pragma once

#include <cstdint>

class Entity {
	uintptr_t currentPawn;
	uintptr_t currentController;

public:
	void Update();
private:
	inline void GetCurrentPawn() {

	}
	inline void GetCurrentController() {

	}
};