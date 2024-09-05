#pragma once
#include "../includes.h"
#include "../Utils/Variable.h"
#include "../Utils/Callfunction.h"



void(__fastcall* Throw_o)(void* self, Vector3 forward, Vector3 position, Quaternion rotation, std::byte utilIndex);
void __stdcall Throw_hook(void* self, Vector3 forward, Vector3 position, Quaternion rotation, std::byte utilIndex) {
	std::cout << (int)utilIndex << std::endl;


	for (int i = 0; i < Menu::NadeMultiply; i++)
	{
		Throw_o(self, Vector3(forward.x * Menu::NadeVeloMultiply, forward.y * Menu::NadeVeloMultiply, forward.z * Menu::NadeVeloMultiply), position, rotation, utilIndex);

		if (Menu::Nuke)
		{

		
			for (void* playerVoid : Variable::Players) {

				std::cout << "throw";
				uintptr_t player = (uintptr_t)playerVoid;
				void* movementManag = *reinterpret_cast<void**>((uintptr_t)(player)+Offsets::playermovement_offset);
				Vector3 Position = *reinterpret_cast<Vector3*>((uintptr_t)(movementManag)+Offsets::movementOffset);
				Throw_o(self, Vector3(0, 0,0), Position, rotation, utilIndex);
			}
		}
	}



}


void(__fastcall* PlayerStart_o)(void* self);
void __stdcall PlayerStart_hook(void* self) {

	PlayerStart_o(self);
	std::cout << "player created \n";

	void* playeridentity = *reinterpret_cast<void**>((uintptr_t)(self)+Offsets::playeridentity_offset);
	std::cout << "player identity \n";
	if (*reinterpret_cast<bool*>((uintptr_t)playeridentity + 0x22) == true)
	{
		std::cout << "player is local \n";
		Variable::LocalPlayer = self;
		std::cout << "local player adress : " << (uintptr_t)self << std::endl;
		Variable::LocalCamera = *reinterpret_cast<void**>((uintptr_t)(self)+Offsets::CameraOffset);
		Variable::LocalPlayerMovement = *reinterpret_cast<void**>((uintptr_t)(self)+Offsets::playermovement_offset);
	}
	else
	{
		std::cout << "Added Player To List";
		Variable::Players.insert(self);
	}

}


void(__fastcall* PlayerDestroy_o)(void* self);
void __stdcall PlayerDestroy_hook(void* self) {

	void* playeridentity = *reinterpret_cast<void**>((uintptr_t)self + Offsets::playeridentity_offset);
	if (*reinterpret_cast<bool*>((uintptr_t)playeridentity + 0x22) == true)
	{
		Variable::LocalPlayer = NULL;
		std::cout << "Local player Destroyed : " << (uintptr_t)self << std::endl;
		Variable::Players.clear();
	}
	else
	{
		std::cout << "player Destroyed \n";
		Variable::Players.erase(self);
	}
	PlayerDestroy_o(self);

}



void(__fastcall* Function_o)(void* self);
void __stdcall Function_hook(void* self) {

	std::cout << "gun created";
	Function_o(self);

}



