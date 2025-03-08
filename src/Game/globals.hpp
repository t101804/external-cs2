#pragma once

#include "Sdk/sdk.h"

#define MAX_ENTITIES_IN_LIST 512
#define MAX_ENTITY_LISTS 64
#define MAX_TOTAL_ENTITIES MAX_ENTITIES_IN_LIST*MAX_ENTITY_LISTS

namespace Globals {
	
	inline void EntityRenderUpdate() {
		// do something
		while (GlobalsConfig.Run) {
			uintptr_t entityList = read_mem<uintptr_t>(Cs2::client_dll + Sdk::offsets::client_dll::dwEntityList);
			for (int i = 1; i < MAX_ENTITY_LISTS; i++) {
				uintptr_t listEntry = read_mem<uintptr_t>(entityList + (8 * (i & 0x7FFF) >> 9) + 16);
				if (!listEntry) {
					continue;
				}
				uintptr_t currentController = read_mem<uintptr_t>(listEntry+120*(i&0x1FF));
				if (!currentController) {
					continue;
				}
				uint32_t pawnHandle = read_mem<uint32_t>(currentController + Sdk::schemas::client_dll::CCSPlayerController::m_hPlayerPawn);
				if (!pawnHandle) {
					continue;
				}
				uintptr_t listEntry2 = read_mem<uintptr_t>(entityList + 0x8 * ((pawnHandle & 0x7FFF) >> 9) + 16);
				if (!listEntry2) {
					continue;
				}
				uintptr_t currentPawn = read_mem<uintptr_t>(listEntry2 + 120 * (pawnHandle & 0x1FF));
				if (!currentPawn) {
					continue;
				}
				int Health = read_mem<int>(currentPawn + Sdk::schemas::client_dll::C_BaseEntity::m_iHealth);
				Logging::debug_print("Health: %d", Health);
				// do something
			}
		}
	}
}