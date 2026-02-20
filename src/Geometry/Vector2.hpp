//
// Created by Igoresha on 20.02.2026.
//

#ifndef RENDERER_VECTOR2_HPP
#define RENDERER_VECTOR2_HPP
#include <complex>

class Vector2 {
public:
    int x; int y;
    Vector2(int x, int y) : x(x), y(y) {}

    Vector2 operator+(const Vector2& v) const {
        return Vector2(x + v.x, y + v.y);
    }

    Vector2 operator-(const Vector2& v) const {
        return Vector2(x - v.x, y - v.y);
    }

    float magnitude() const {
        return std::sqrt(x * x + y * y);
    }
};



#endif //RENDERER_VECTOR2_HPP