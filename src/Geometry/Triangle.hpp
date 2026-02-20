//
// Created by Igor on 20.02.2026.
//

#ifndef RENDERER_TRIANGLE_HPP
#define RENDERER_TRIANGLE_HPP
#include "Matrix4.hpp"
#include "Vector3.hpp"
#include "structs/Barycentric.hpp"
#include "structs/BoundingBox.hpp"


class Triangle {

public:
    Vector3 v0, v1, v2;
    Triangle(Vector3 p1, Vector3 p2, Vector3 p3): v0(p1), v1(p2), v2(p3) {}
private:
    float Edge(const Vector3& a, const Vector3& b, const Vector3& c) const
    {
        return (c.x - a.x) * (b.y - a.y) - (c.y - a.y) * (b.x - a.x);
    }

public:
    BoundingBox GetBoundingBox() const {
        return {
        static_cast<int>(floor(std::min(std::min(v0.x, v1.x), v2.x))),
        static_cast<int>(floor(std::min(std::min(v0.y, v1.y), v2.y))),
        static_cast<int>(ceil(std::max(std::max(v0.x, v1.x), v2.x))),
        static_cast<int>(ceil(std::max(std::max(v0.y, v1.y), v2.y))),
        };
    }

    Barycentric ComputeBarycentric(const Vector3& p) const
    {
        return {
            Edge(v1, v2, p),
            Edge(v2, v0, p),
            Edge(v0, v1, p)
        };
    }

    static Vector3 Transform(const Vector3 &v, Matrix4 m)
    {
        Vector4 temp(v.x, v.y, v.z, 1.0f);
        Vector4 result = m * temp;

        return Vector3{
            result.x,
            result.y,
            result.z
        };
    }
    Triangle TransformTriangle(const Matrix4& m) const {
        return {
            Transform(this->v0, m),
            Transform(this->v1, m),
            Transform(this->v2, m)
        };
    }

    static Vector3 PerspectiveProjection(const Vector3& v, int screenWidth, int screenHeight)
    {
        float f = 400.0f;

        float projectedX = (v.x * f) / (v.z + f);
        float projectedY = (v.y * f) / (v.z + f);

        projectedX += screenWidth / 2.0f;
        projectedY += screenHeight / 2.0f;

        return { projectedX, projectedY, v.z };
    }

    Triangle ProjectTriangle(int screenWidth, int screenHeight) const
    {
        return {
            PerspectiveProjection(v0, screenWidth, screenHeight),
            PerspectiveProjection(v1, screenWidth, screenHeight),
            PerspectiveProjection(v2, screenWidth, screenHeight)
        };
    }
};


#endif //RENDERER_TRIANGLE_HPP