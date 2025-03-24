#include "entity.h"

// EntityController Controller;


uintptr_t GetBoneMatrix(uintptr_t entityPawn)
{
	uintptr_t node = read_mem<uintptr_t>(entityPawn + Sdk::schemas::client_dll::C_BaseEntity::m_pGameSceneNode); // m_pGameSceneNode
	uintptr_t boneMatrix = read_mem<uintptr_t>(node + Sdk::schemas::client_dll::CSkeletonInstance::m_modelState + 0x80); // m_groundNormal 
	return boneMatrix;
}

//enum 
bool Entity::Update() {
	// do something
	Team = read_mem<int>(Controller.currentPawn + Sdk::schemas::client_dll::C_BaseEntity::m_iTeamNum);
	Health = read_mem<int>(Controller.currentPawn + Sdk::schemas::client_dll::C_BaseEntity::m_iHealth);
	Armor = read_mem<int>(Controller.currentPawn + Sdk::schemas::client_dll::C_CSPlayerPawn::m_ArmorValue);
	if (Health == 0) {
		return false;
	}
	uintptr_t gameSceneNode = read_mem<uintptr_t>(Controller.currentPawn + Sdk::schemas::client_dll::C_BaseEntity::m_pGameSceneNode);
	Position = read_mem<Vector3>(gameSceneNode + Sdk::schemas::client_dll::CGameSceneNode::m_vecAbsOrigin);
	BoneMatrix = GetBoneMatrix(Controller.currentPawn);
	if (BoneMatrix == 0) {
		return false;
	}
	uintptr_t CurrentWeapon = read_mem <uintptr_t>(Controller.currentPawn+Sdk::schemas::client_dll::C_CSPlayerPawnBase::m_pClippingWeapon);
	short rawWeaponIndex = read_mem<short>(CurrentWeapon + Sdk::schemas::client_dll::C_EconEntity::m_AttributeManager + Sdk::schemas::client_dll::C_AttributeContainer::m_Item + Sdk::schemas::client_dll::C_EconItemView::m_iItemDefinitionIndex );
	
	WeaponIndexes weapon = static_cast<WeaponIndexes>(rawWeaponIndex);
	CurrentWeaponName = getWeaponName(weapon);
	// Logging::debug_print("weapon : %s", CurrentWeaponName.c_str());
	return true;
}
