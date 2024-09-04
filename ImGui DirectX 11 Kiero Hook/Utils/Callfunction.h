#pragma once
#include "Struct.h"
#include <windows.h> 
#include "../cheat.h"


typedef Vector3(__cdecl* WorldToScreenPointFn)(void*, Vector3);
Vector3 WorldToScreenPoint(void* camera, Vector3 position);

typedef Vector3(__cdecl* GetBonePosFn)(void*);

typedef void* (__cdecl* GetMainCamFn)(void*);
void* GetMainCam(void* self);

Vector3 GetBonePos(void* self);


