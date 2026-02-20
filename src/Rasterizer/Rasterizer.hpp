//
// Created by Igor on 20.02.2026.
//

#ifndef RENDERER_RASTERIZER_HPP
#define RENDERER_RASTERIZER_HPP
#include "../Geometry/Triangle.hpp"
#include "../Renderer/Renderer.hpp"


class Rasterizer {
private:
    Renderer* renderer;
public:
    Rasterizer(Renderer* renderer): renderer(renderer) {};

    void DrawTriangle(Triangle*triangle, int rColor = 255, int gColor = 128, int bColor = 0) {
        auto [minX, minY, maxX, maxY] = triangle->GetBoundingBox();

        for (int y = minY; y <= maxY; y++)
        {
            for (int x = minX; x <= maxX; x++)
            {
                Vector2*p = new Vector2(x + 0.5f, y + 0.5f);
                auto [w0,w1,w2] = triangle->ComputeBarycentric(*p);

                if ((w0 >= 0 && w1 >= 0 && w2 >= 0) || (w0 <= 0 && w1 <= 0 && w2 <= 0))
                {
                    this->renderer->DrawPixel(x, y, rColor, gColor, bColor);
                }
                delete p;
            }
        }
    }
};


#endif //RENDERER_RASTERIZER_HPP