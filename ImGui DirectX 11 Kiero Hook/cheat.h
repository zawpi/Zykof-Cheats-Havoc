#pragma once
void ImguiWindow();
void CheatMain();
void HookFunction();


namespace Offsets {
    constexpr uintptr_t playerSart = 0x51a440;
    constexpr uintptr_t playerdestroy = 0x50f790;
    constexpr uintptr_t walloffset = 0x5b0b50;
    constexpr uintptr_t FOVCAM_offset = 0x190;
    constexpr uintptr_t FOVGUN_offset = 0x19C;
    constexpr uintptr_t playermovement_offset = 0x310;
    constexpr uintptr_t worldToScreenPointOffset = 0x2127500;
    constexpr uintptr_t playeridentity_offset = 0x358;
    constexpr uintptr_t aimbot_weaponmanager_offset = 0x348;
    constexpr uintptr_t movementOffset = 0x390;
    constexpr uintptr_t LimbSystemOffset = 0x410;
    constexpr uintptr_t gibBonesOnPlayeroffset = 0x48;
    constexpr uintptr_t get_positionOffset = 0x21700d0;
    constexpr uintptr_t GetBonePosOffset = 0x2170650;
    constexpr uintptr_t playerInitialiseOffSet = 0x318;
    constexpr uintptr_t BodyRenderOffSet = 0x90;
    constexpr uintptr_t GetShaderOffset = 0x2136280;
    constexpr uintptr_t CameraOffset = 0x2f0;
    constexpr uintptr_t functionTest = 0x5c42c0;

}

extern uintptr_t GameAssembly;