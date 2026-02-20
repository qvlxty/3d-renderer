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

        // ToDo: когда поменяем проекцию, эту фикстуру снести лол
        minX = std::max(0, minX);
        minY = std::max(0, minY);
        maxX = std::min(this->renderer->winWidth, maxX);
        maxY = std::min(this->renderer->winHeight, maxY);

        for (int y = minY; y <= maxY; y++)
        {
            for (int x = minX; x <= maxX; x++)
            {
                Vector3*p = new Vector3(x + 0.5f, y + 0.5f, 0);
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