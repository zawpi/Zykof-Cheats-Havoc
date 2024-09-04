#include "utils.h"
#include <set>
#include "./Struct.h"
#include "../includes.h"

Vector2 GetMousePosition() {
    POINT p;
    if (GetCursorPos(&p)) {
        return Vector2(static_cast<float>(p.x), static_cast<float>(p.y));
    }
    return Vector2(0.0f, 0.0f);
}



void MoveMouseBy(Vector2 offset) {
    std::cout << "moved mouse \n";
    mouse_event(MOUSEEVENTF_MOVE, static_cast<DWORD>(offset.x), static_cast<DWORD>(offset.y), 0, 0);
}



float Calculate3DDistance(Vector3 a, Vector3 b) {
    return sqrt(pow(a.x - b.x, 2) + pow(a.y - b.y, 2) + pow(a.z - b.z, 2));
}

float CalculateDistance(Vector2 a, Vector2 b) {
    float dx = a.x - b.x;
    float dy = a.y - b.y;
    return sqrt(dx * dx + dy * dy);
}