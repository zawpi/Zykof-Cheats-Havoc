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
    extern bool AimBotDraw;
    extern float AimBotColor[3];
    extern float ESPColor[3];
    extern std::string actualMenu;
    extern RECT Gamerect;
    extern int Gamewidth, Gameheight;
    extern bool ESPenabled;
    extern int NadeMultiply;
    extern int NadeVeloMultiply;
    extern bool Nuke;
}

