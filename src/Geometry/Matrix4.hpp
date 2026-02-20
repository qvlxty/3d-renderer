//
// Created by Igor on 21.02.2026.
//

#ifndef RENDERER_MATRIX4_HPP
#define RENDERER_MATRIX4_HPP
#include <cmath>

#include "Vector4.hpp"


class Matrix4 {
    float m[4][4];
public:
    Matrix4() {
        this->Identity();
    }

public:
    void Identity() {
        for (int i = 0; i < 4; i++)
            for (int j = 0; j < 4; j++)
                m[i][j] = (i == j) ? 1.0f : 0.0f;
    }

    void RotationY(float angle)
    {
        this->Identity();

        float c = cosf(angle);
        float s = sinf(angle);

        m[0][0] =  c;
        m[0][2] =  s;

        m[2][0] = -s;
        m[2][2] =  c;
    }
    void RotationZ(float angle) {
        this->Identity();

        float c = cosf(angle);
        float s = sinf(angle);

        m[0][0] =  c;
        m[0][1] = -s;

        m[1][0] =  s;
        m[1][1] =  c;
    }
    // Бинарное умножение именно матрицы на вектор, над не забыть
    Vector4 operator*(const Vector4& v) const {
        Vector4 r;

        r.x = m[0][0]*v.x + m[0][1]*v.y + m[0][2]*v.z + m[0][3]*v.w;
        r.y = m[1][0]*v.x + m[1][1]*v.y + m[1][2]*v.z + m[1][3]*v.w;
        r.z = m[2][0]*v.x + m[2][1]*v.y + m[2][2]*v.z + m[2][3]*v.w;
        r.w = m[3][0]*v.x + m[3][1]*v.y + m[3][2]*v.z + m[3][3]*v.w;

        return r;
    }
};


#endif //RENDERER_MATRIX4_HPP