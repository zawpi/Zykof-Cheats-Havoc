#pragma once
#include "../includes.h"
#include "../Utils/Variable.h"
#include "../Utils/Struct.h"
#include "../Utils/Callfunction.h"
#include "../Utils/utils.h"
#include <algorithm>


#include <iostream>

void AimBot() {
    if (Menu::AimBotEnable) {
        float minDist = 99999.0f;
        Vector3 AimTarget = Vector3(0, 0, 0);
        Vector3 playertargetpos = Vector3(0, 0, 0);
        Vector3 playerpos = Vector3(0, 0, 0);
        float distance3d = 0;
        int array_length = 0;
        uintptr_t array_address = NULL;


        for (void* playerVoid : Variable::Players) {
            uintptr_t player = (uintptr_t)playerVoid;
            void* playerlimbsystem = *reinterpret_cast<void**>(player + Offsets::LimbSystemOffset);

            if (!playerlimbsystem) {
                std::cout << "Invalid player limb system" << std::endl;
                continue;
            }

            array_address = *reinterpret_cast<uintptr_t*>((uintptr_t)(playerlimbsystem)+0x48);
            if (!array_address) {

                continue;
            }

            array_length = *reinterpret_cast<int*>(array_address + 0x18);
            if (array_length < 9) {

                continue;
            }

            void* transform_address = *reinterpret_cast<void**>(array_address + 0x20 + (8 * sizeof(uintptr_t)));
            if (!transform_address) {

                continue;
            }

            playerpos = GetBonePos(transform_address);

            Vector3 screenPosition = WorldToScreenPoint(Variable::LocalCamera, playerpos);



            if (screenPosition.z <= 0.0f) {

                continue;
            }

            float dist = CalculateDistance(Vector2(screenPosition.x, screenPosition.y), { static_cast<float>(1920 / 2), static_cast<float>(1080 / 2) });



            if (dist < Menu::FovAimBot && dist < minDist) {
                minDist = dist;
                AimTarget = screenPosition;
                playertargetpos = playerpos;


                AimTarget.Print();

                playertargetpos.Print();
            }
        }

        distance3d = Calculate3DDistance(Variable::LocalPlayerPosition, playertargetpos);



        void* aimbot_weaponmanager = *reinterpret_cast<void**>((uintptr_t)Variable::LocalPlayer + Offsets::aimbot_weaponmanager_offset);
        if ((AimTarget.x != 0.0f && AimTarget.y != 0.0f) && (1 == *(int*)((uintptr_t)aimbot_weaponmanager + 0x150))) {
            Vector2 currentMousePos = GetMousePosition();
            Vector2 aimPos(AimTarget.x, AimTarget.y);
            Vector2 offset = { aimPos.x - currentMousePos.x, aimPos.y - currentMousePos.y };
            float smooth = Menu::AimBotSmooth;
            offset.x /= smooth;
            offset.y /= smooth;



            MoveMouseBy(Vector2(offset.x, -offset.y));
        }

    }
}

