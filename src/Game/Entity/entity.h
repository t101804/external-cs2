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

//struct Player {
//    int Team;
//    int Health;
//    int Armor;
//    char Names[128] = { 0 };
//    Vector3 Position;
//    uintptr_t BoneMatrix;
//    bool IsFiring;
//    uint32_t Ping;
//    Vector3 VecViewOffset;
//    bool IsScoped;
//    bool IsDormant;
//};

class Entity {
public:
	EntityController Controller;
    int Team;
    int Health;
    int Armor;
    std::string CurrentWeaponName;
    char Names[128] = { 0 };
    Vector3 Position;
    uintptr_t BoneMatrix;
    bool IsFiring;
    uint32_t Ping;
    Vector3 VecViewOffset;
    bool IsScoped;
    bool IsDormant;
	// Player player;

public:
    int Index;
	bool Update();
private:

    std::string getWeaponName(WeaponIndexes weapon) {
        switch (weapon) {
        case Invalid:                     return "Invalid";
        case Deagle:                      return "Deagle";
        case Elite:                       return "Elite";
        case Fiveseven:                   return "Fiveseven";
        case Glock:                       return "Glock";
        case Ak47:                        return "Ak47";
        case Aug:                         return "Aug";
        case Awp:                         return "Awp";
        case Famas:                       return "Famas";
        case G3Sg1:                       return "G3SG1";
        case Galilar:                     return "Galilar";
        case M249:                        return "M249";
        case M4A1:                        return "M4A1";
        case Mac10:                       return "Mac10";
        case P90:                         return "P90";
        case Mp5:                         return "Mp5";
        case Ump45:                       return "Ump45";
        case Xm1014:                      return "XM1014";
        case Bizon:                       return "Bizon";
        case Mag7:                        return "Mag7";
        case Negev:                       return "Negev";
        case Sawedoff:                    return "Sawedoff";
        case Tec9:                        return "Tec9";
        case Taser:                       return "Taser";
        case Hkp2000:                     return "Hkp2000";
        case Mp7:                         return "Mp7";
        case Mp9:                         return "Mp9";
        case Nova:                        return "Nova";
        case P250:                        return "P250";
        case Shield:                      return "Shield";
        case Scar20:                      return "Scar20";
        case Sg556:                       return "Sg556";
        case Ssg08:                       return "Ssg08";
        case Knifegg:                     return "Knifegg";
        case Knife:                       return "Knife";
        case Flashbang:                   return "Flashbang";
        case Hegrenade:                   return "Hegrenade";
        case Smokegrenade:                return "Smokegrenade";
        case Molotov:                     return "Molotov";
        case Decoy:                       return "Decoy";
        case Incgrenade:                  return "Incgrenade";
        case C4:                          return "C4";
        case Healthshot:                  return "Healthshot";
        case KnifeT:                      return "KnifeT";
        case M4A1Silencer:                return "M4A1Silencer";
        case UspSilencer:                 return "UspSilencer";
        case Cz75A:                       return "Cz75A";
        case Revolver:                    return "Revolver";
        case Tagrenade:                   return "Tagrenade";
        case Fists:                       return "Fists";
        case Breachcharge:                return "Breachcharge";
        case Tablet:                      return "Tablet";
        case Melee:                       return "Melee";
        case Axe:                         return "Axe";
        case Hammer:                      return "Hammer";
        case Spanner:                     return "Spanner";
        case KnifeGhost:                  return "KnifeGhost";
        case Firebomb:                    return "Firebomb";
        case Diversion:                   return "Diversion";
        case FragGrenade:                 return "FragGrenade";
        case Snowball:                    return "Snowball";
        case Bumpmine:                    return "Bumpmine";
        case Bayonet:                     return "Bayonet";
        case KnifeFlip:                   return "KnifeFlip";
        case KNIFE_GUT:                   return "KNIFE_GUT";
        case KNIFE_KARAMBIT:              return "KNIFE_KARAMBIT";
        case KNIFE_M9_BAYONET:            return "KNIFE_M9_BAYONET";
        case KNIFE_TACTICAL:              return "KNIFE_TACTICAL";
        case KNIFE_FALCHION:              return "KNIFE_FALCHION";
        case KNIFE_SURVIVAL_BOWIE:         return "KNIFE_SURVIVAL_BOWIE";
        case KNIFE_BUTTERFLY:             return "KNIFE_BUTTERFLY";
        case KNIFE_PUSH:                  return "KNIFE_PUSH";
        case KNIFE_URSUS:                 return "KNIFE_URSUS";
        case KNIFE_GYPSY_JACKKNIFE:       return "KNIFE_GYPSY_JACKKNIFE";
        case KNIFE_STILETTO:              return "KNIFE_STILETTO";
        case KNIFE_WIDOWMAKER:            return "KNIFE_WIDOWMAKER";
        case GLOVE_STUDDED_BLOODHOUND:      return "GLOVE_STUDDED_BLOODHOUND";
        case GLOVE_T_SIDE:                return "GLOVE_T_SIDE";
        case GLOVE_CT_SIDE:               return "GLOVE_CT_SIDE";
        case GLOVE_SPORTY:                return "GLOVE_SPORTY";
        case GLOVE_SLICK:                 return "GLOVE_SLICK";
        case GLOVE_LEATHER_WRAP:          return "GLOVE_LEATHER_WRAP";
        case GLOVE_MOTORCYCLE:            return "GLOVE_MOTORCYCLE";
        case GLOVE_SPECIALIST:            return "GLOVE_SPECIALIST";
        case GLOVE_HYDRA:                 return "GLOVE_HYDRA";
        default:                          return "Unknown Weapon";
        }
    }

	inline void GetCurrentPawn() {

	}
	inline void GetCurrentController() {

	}
};