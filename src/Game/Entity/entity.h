#pragma once

#include <cstdint>
#include "../../Utils/Log/log.h"
#include "../Sdk/sdk.h"
//#include "../globals.hpp"
//
//EntityController Controller;


struct EntityController {
	uintptr_t currentPawn;
	uintptr_t currentController;
};

struct Player {
    int Team;
    int Health;
    int Armor;
    char Names[128] = { 0 };
    Vector3 Position;
    uintptr_t BoneMatrix;
    bool IsFiring;
    uint32_t Ping;
    Vector3 VecViewOffset;
    bool IsScoped;
    bool IsDormant;
};

class Entity {
public:
	EntityController Controller;
	Player player;

public:

	void Update();
private:
	inline void GetCurrentPawn() {

	}
	inline void GetCurrentController() {

	}
};