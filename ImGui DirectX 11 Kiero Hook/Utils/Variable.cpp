// Variable.cpp
#include "Struct.h"
#include <windows.h> 
#include "../cheat.h"
#include "Callfunction.h"
#include <set>
namespace Variable {
    void* LocalPlayerMovement = nullptr;
    Vector3 LocalPlayerPosition = {};
    std::set<void*> Players;
    int FOVCam = 103.0f;
    int FOVGun = 60.0f;
    void* LocalCamera = NULL;
    void* LocalPlayer = NULL;
}

namespace Menu {
    bool AimBotEnable = false;
    bool AimBotDraw = false;
    float AimBotColor[3] = { 1.0f, 0.0f, 0.0f };
    float ESPColor[3] = { 1.0f, 0.0f, 0.0f };
    bool showMenu = false;
    std::string actualMenu = "";
    float AimBotSmooth = 5.0f;
    float FovAimBot = 300.0f;
    RECT Gamerect = {};
    int Gamewidth = 0;
    int Gameheight = 0;
    bool ESPenabled = false;
}
