#pragma once
#include <cmath>
#include <iostream>

class Vector3 {
public:
    float x, y, z;

    Vector3() : x(0), y(0), z(0) {}
    Vector3(float x, float y, float z) : x(x), y(y), z(z) {}

    // Overload the + operator
    Vector3 operator+(const Vector3& other) const {
        return Vector3(x + other.x, y + other.y, z + other.z);
    }

    // Overload the - operator
    Vector3 operator-(const Vector3& other) const {
        return Vector3(x - other.x, y - other.y, z - other.z);
    }

    // Overload the * operator
    Vector3 operator*(float scalar) const {
        return Vector3(x * scalar, y * scalar, z * scalar);
    }

    // Overload the / operator
    Vector3 operator/(float scalar) const {
        return Vector3(x / scalar, y / scalar, z / scalar);
    }

    // Print Vector3 for debugging
    void Print() const {
        std::cout << "Vector3(" << x << ", " << y << ", " << z << ")\n";
    }
};


class Vector2 {
public:
    float x;
    float y;
    Vector2() : x(0), y(0) {}
    Vector2(float x1, float y1) : x(x1), y(y1) {}
};


struct Quaternion {
    float x, y, z, w;
};




struct Color
{
    float r, g, b, a;

    Color() { r = g = b = a = 0.f; }
    Color(float fRed = 0.f, float fGreen = 0.f, float fBlue = 0.f, float fAlpha = 1.f) { r = fRed; g = fGreen; b = fBlue; a = fAlpha; }
};


