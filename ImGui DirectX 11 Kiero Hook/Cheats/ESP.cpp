#pragma once
#include "../includes.h"
#include "../Utils/Variable.h"
#include "../Utils/Struct.h"
#include "../Utils/utils.h"
#include "../Utils/Callfunction.h"
#include <algorithm>
#include <iostream> 

void DrawESP() {
    uintptr_t array_address = NULL;
    int array_length = 0;

    for (void* playerVoid : Variable::Players) {
        uintptr_t player = (uintptr_t)playerVoid;
        void* movementManag = *reinterpret_cast<void**>((uintptr_t)(player)+Offsets::playermovement_offset);
        Vector3 Position = *reinterpret_cast<Vector3*>((uintptr_t)(movementManag)+Offsets::movementOffset);
        Vector3 corners[] = {
            WorldToScreenPoint(Variable::LocalCamera, Vector3(Position.x - 0.5, Position.y, Position.z - 0.5)),
            WorldToScreenPoint(Variable::LocalCamera, Vector3(Position.x + 0.5, Position.y, Position.z - 0.5)),
            WorldToScreenPoint(Variable::LocalCamera, Vector3(Position.x - 0.5, Position.y + 1.8, Position.z + 0.5)),
            WorldToScreenPoint(Variable::LocalCamera, Vector3(Position.x + 0.5, Position.y + 1.8, Position.z + 0.5))
        };

        for (auto& corner : corners) {
            corner.y = Menu::Gameheight - corner.y;
        }

        if (std::all_of(std::begin(corners), std::end(corners), [](const Vector3& corner) { return corner.z > 0; })) {
            float minX = std::min_element(std::begin(corners), std::end(corners), [](const Vector3& a, const Vector3& b) { return a.x < b.x; })->x;
            float maxX = std::max_element(std::begin(corners), std::end(corners), [](const Vector3& a, const Vector3& b) { return a.x < b.x; })->x;
            float minY = std::min_element(std::begin(corners), std::end(corners), [](const Vector3& a, const Vector3& b) { return a.y < b.y; })->y;
            float maxY = std::max_element(std::begin(corners), std::end(corners), [](const Vector3& a, const Vector3& b) { return a.y < b.y; })->y;

            ImGui::GetForegroundDrawList()->AddRect(ImVec2(minX, minY), ImVec2(maxX, maxY), ImColor(Menu::ESPColor[0], Menu::ESPColor[1], Menu::ESPColor[2], 1.0f));
        }
    }
}

