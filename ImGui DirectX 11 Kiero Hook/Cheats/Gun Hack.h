#pragma once
#include "../includes.h"
#include "../Utils/Variable.h"
#include "../Utils/Struct.h"
#include "../Utils/Callfunction.h"
#include "../Utils/utils.h"
#include <algorithm>



uintptr_t player;

uintptr_t weaponManager;

uintptr_t currentGun;

uintptr_t GunDef;

void GetVar() {

	player = (uintptr_t)Variable::LocalPlayer;
	std::cout << "get player " << player << std::endl;
	weaponManager = (uintptr_t)*reinterpret_cast<void**>(player + Offsets::aimbot_weaponmanager_offset);
	std::cout << "get weaponManager " << weaponManager << std::endl;
	currentGun = (uintptr_t) * reinterpret_cast<void**>(weaponManager + Offsets::CurrentGunOffset);
	std::cout << "get gun " << currentGun << std::endl;
	GunDef = (uintptr_t) * reinterpret_cast<void**>(currentGun + Offsets::GunDef);
	std::cout << "get def " << GunDef << std::endl;
}


void OneShot()
{
	GetVar();
	*reinterpret_cast<float*>(GunDef + Offsets::bodyDamage) = 999.0f;
}


void WallBang()
{
	GetVar();
	*reinterpret_cast<float*>(GunDef + Offsets::GunPenetration) = 999.0f;
}

void FireRate()
{
	GetVar();
	*reinterpret_cast<float*>(GunDef + Offsets::GunFireRate) = *reinterpret_cast<float*>(GunDef + Offsets::GunFireRate) * 900;
}

void Recoil()
{
	GetVar();
	*reinterpret_cast<int*>(GunDef + Offsets::RecoilTime) = 0;
}

void NoInaccuracy()
{
	GetVar();
	*reinterpret_cast<int*>(GunDef + Offsets::MaxInaccurate) = 1;
}

void infiniteAmmo()
{
	GetVar();
	*reinterpret_cast<int*>(currentGun + Offsets::currentAmmo) = *reinterpret_cast<int*>(currentGun + Offsets::currentAmmo) * 999;
}