#include "entity.h"

// EntityController Controller;


uintptr_t GetBoneMatrix(uintptr_t entityPawn)
{
	uintptr_t node = read_mem<uintptr_t>(entityPawn + Sdk::schemas::client_dll::C_BaseEntity::m_pGameSceneNode); // m_pGameSceneNode
	uintptr_t boneMatrix = read_mem<uintptr_t>(node + 0x1F0); // m_groundNormal 
	return boneMatrix;
}

bool Entity::Update() {
	// do something
	player.Team = read_mem<int>(Controller.currentPawn + Sdk::schemas::client_dll::C_BaseEntity::m_iTeamNum);
	player.Health = read_mem<int>(Controller.currentPawn + Sdk::schemas::client_dll::C_BaseEntity::m_iHealth);
	player.Armor = read_mem<int>(Controller.currentPawn + Sdk::schemas::client_dll::C_CSPlayerPawn::m_ArmorValue);
	/*player.Position = read_mem<Vector3>(Controller.currentPawn + Sdk::schemas::client_dll::C_BasePlayerPawn::m_vOldOrigin);
	if (player.Position.x == 0 && player.Position.y == 0 && player.Position.z == 0) {
		return false;
	}*/
	uintptr_t gameSceneNode = read_mem<uintptr_t>(Controller.currentPawn + Sdk::schemas::client_dll::C_BaseEntity::m_pGameSceneNode);
	player.Position = read_mem<Vector3>(gameSceneNode + Sdk::schemas::client_dll::CGameSceneNode::m_vecAbsOrigin);
	if (player.Position.x == 0.f && player.Position.y == 0.f) {
		return false;
	}
	player.BoneMatrix = GetBoneMatrix(Controller.currentPawn);
	if (player.BoneMatrix == 0) {
		return false;
	}
	//player.BoneMatrix = read_mem<uintptr_t>(Controller.currentPawn + Sdk::schemas::client_dll::C_BasePlayerPawn::m_dwBoneMatrix);
	//Logging::debug_print("ControllerPawn: %p", Controller.currentPawn);
	return true;
}
