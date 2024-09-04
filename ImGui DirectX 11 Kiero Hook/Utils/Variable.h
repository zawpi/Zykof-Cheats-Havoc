#pragma once
#include <set>
#include "Struct.h"


namespace Variable {
    extern void* LocalPlayer;
    extern void* LocalCamera;
    extern void* LocalPlayerMovement;
    extern Vector3 LocalPlayerPosition;
    extern std::set<void*> Players;
    extern int FOVCam;
    extern int FOVGun;
}

namespace Menu {
    extern bool showMenu;
    extern bool AimBotEnable;
    extern float AimBotSmooth;
    extern float FovAimBot;
    extern std::string actualMenu;
    extern RECT Gamerect;
    extern int Gamewidth, Gameheight;
    extern bool ESPenabled;
}

