//
// Created by Igor on 21.02.2026.
//

#ifndef RENDERER_CUBE_HPP
#define RENDERER_CUBE_HPP

#include "../Geometry/Vector3.hpp"
#include "../Geometry/Triangle.hpp"

class Square {
public:
    Triangle *first, * second;
    Square(Vector3 a, Vector3 b, Vector3 c, Vector3 d) {
        first = new Triangle(a, b, c);
        second = new Triangle(b, c, d);
    }
    ~Square() {
        delete first;
        delete second;
    }
};

class Cube {
    public:

    Cube(float size = 200) {
        float h = size / 2.0f;

        Vector3 p000 = {-h, -h, -h};
        Vector3 p100 = { h, -h, -h};
        Vector3 p010 = {-h,  h, -h};
        Vector3 p110 = { h,  h, -h};

        Vector3 p001 = {-h, -h,  h};
        Vector3 p101 = { h, -h,  h};
        Vector3 p011 = {-h,  h,  h};
        Vector3 p111 = { h,  h,  h};

        squares[0] = new Square(p000, p100, p010, p110);
        squares[1] = new Square(p101, p001, p111, p011);
        squares[2] = new Square(p001, p000, p011, p010);
        squares[3] = new Square(p100, p101, p110, p111);
        squares[4] = new Square(p000, p001, p100, p101);
        squares[5] = new Square(p010, p110, p011, p111);
    }

    ~Cube() {
        for (auto iter: squares) {
            delete iter;
        }
    }

    Square *squares[6];

};


#endif //RENDERER_CUBE_HPP