#pragma once
#include "../Utils/Variable.h"
#include "../cheat.h"
void Fov() {
	int CurrentCamFov = *reinterpret_cast<int*>((uintptr_t)Variable::LocalPlayer + Offsets::FOVCAM_offset);
	int CurrentGunFov = *reinterpret_cast<int*>((uintptr_t)Variable::LocalPlayer + Offsets::FOVGUN_offset);

	if (Variable::FOVCam != CurrentCamFov)
	{
		*reinterpret_cast<float*>((uintptr_t)Variable::LocalPlayer + Offsets::FOVCAM_offset) = Variable::FOVCam;
	}

	if (Variable::FOVGun != CurrentGunFov)
	{
		*reinterpret_cast<float*>((uintptr_t)Variable::LocalPlayer + Offsets::FOVGUN_offset) = Variable::FOVGun;
	}
}
