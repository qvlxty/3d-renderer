//
// Created by Igor on 20.02.2026.
//

#ifndef RENDERER_VERTEX_HPP
#define RENDERER_VERTEX_HPP
#include "Vector2.hpp"
#include "Vector3.hpp"


class Vertex {
public:
    Vertex(Vector3 position, Vector2 uv): position(position), uv(uv) {}
    Vertex(Vector3 position): position(position), uv(Vector2(0,0)) {}
    Vector3 position;
    Vector2 uv;
};


#endif //RENDERER_VERTEX_HPP