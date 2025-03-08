#include "entity.h"

// EntityController Controller;


void Entity::Update() {
	// do something
	player.Team = read_mem<int>(Controller.currentPawn + Sdk::schemas::client_dll::C_BaseEntity::m_iTeamNum);
	player.Health = read_mem<int>(Controller.currentPawn + Sdk::schemas::client_dll::C_BaseEntity::m_iHealth);
	player.Armor = read_mem<int>(Controller.currentPawn + Sdk::schemas::client_dll::C_CSPlayerPawn::m_ArmorValue);
	player.Position = read_mem<Vector3>(Controller.currentPawn + Sdk::schemas::client_dll::C_BasePlayerPawn::m_vOldOrigin);
	//player.BoneMatrix = read_mem<uintptr_t>(Controller.currentPawn + Sdk::schemas::client_dll::C_BasePlayerPawn::m_dwBoneMatrix);
	Logging::debug_print("ControllerPawn: %p", Controller.currentPawn);
}