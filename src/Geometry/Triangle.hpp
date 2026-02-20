//
// Created by Igor on 20.02.2026.
//

#ifndef RENDERER_TRIANGLE_HPP
#define RENDERER_TRIANGLE_HPP
#include "Vector2.hpp"
#include "structs/Barycentric.hpp"
#include "structs/BoundingBox.hpp"


class Triangle {

public:
    Vector2 v0, v1, v2;
    Triangle(Vector2 p1, Vector2 p2, Vector2 p3): v0(p1), v1(p2), v2(p3) {}
private:
    float Edge(const Vector2& a, const Vector2& b, const Vector2& c) const
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

    Barycentric ComputeBarycentric(const Vector2& p) const
    {
        return {
            Edge(v1, v2, p),
            Edge(v2, v0, p),
            Edge(v0, v1, p)
        };
    }
};


#endif //RENDERER_TRIANGLE_HPP