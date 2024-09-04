#pragma once
#include "Struct.h"
#include <windows.h> 
#include "../cheat.h"


typedef Vector3(__cdecl* WorldToScreenPointFn)(void*, Vector3);
Vector3 WorldToScreenPoint(void* camera, Vector3 position) {
    WorldToScreenPointFn WorldToScreenPoint_Injected =
        reinterpret_cast<WorldToScreenPointFn>(GameAssembly + Offsets::worldToScreenPointOffset);

    if (!WorldToScreenPoint_Injected) {
        std::cerr << "WorldToScreenPoint function pointer is invalid." << std::endl;
        return Vector3();
    }

    Vector3 screenPosition = WorldToScreenPoint_Injected(camera, position);
    return screenPosition;
}

typedef Vector3(__cdecl* GetBonePosFn)(void*);

Vector3 GetBonePos(void* self) {
    GetBonePosFn GetBonePos_Injected =
        reinterpret_cast<GetBonePosFn>(GameAssembly + Offsets::GetBonePosOffset);

    if (!GetBonePos_Injected) {
        std::cerr << "WorldToScreenPoint function pointer is invalid." << std::endl;
        return Vector3();
    }

    Vector3 screenPosition = GetBonePos_Injected(self);
    return screenPosition;
}

typedef void*(__cdecl* GetMainCamFn)(void*);

void* GetMainCam(void* self) {
    GetMainCamFn GetMainCam_Injected =
        reinterpret_cast<GetMainCamFn>(GameAssembly + 0x21279e0);



    void* screenPosition = GetMainCam_Injected(self);
    return screenPosition;
}


