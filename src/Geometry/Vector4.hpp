//
// Created by Igor on 21.02.2026.
//

#ifndef RENDERER_VECTOR4_HPP
#define RENDERER_VECTOR4_HPP
#include "Vector2.hpp"
#include "Vector3.hpp"


struct Vector4 {
public:
    float x, y, z, w;
    Vector4() { x = 0; y = 0; z = 0; w = 0; }
    Vector4(float x, float y, float z, float w) : x(x), y(y), z(z), w(w) {}
    Vector4(Vector3 v, float w) : x(v.x), y(v.y), z(v.z), w(w) {}
    Vector4(Vector2 v, float z, float w) : x(v.x), y(v.y), z(z), w(w) {}
};


#endif //RENDERER_VECTOR4_HPP