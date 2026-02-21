//
// Created by Igor on 20.02.2026.
//

#ifndef RENDERER_RASTERIZER_HPP
#define RENDERER_RASTERIZER_HPP
#include "../Geometry/Triangle.hpp"
#include "../Renderer/Renderer.hpp"


class Rasterizer {
private:
    Renderer *renderer;

public:
    Rasterizer(Renderer *renderer) : renderer(renderer), zBuffer(renderer->winHeight * renderer->winWidth) {
    };

    void ClearZBuffer() {
        std::fill(zBuffer.begin(), zBuffer.end(), std::numeric_limits<float>::infinity());
    }

    std::vector<float> zBuffer;

    void DrawTriangle(Triangle *triangle, int rColor = 255, int gColor = 128, int bColor = 0) {
        auto [minX, minY, maxX, maxY] = triangle->GetBoundingBox();

        // ToDo: когда поменяем проекцию, эту фикстуру снести лол
        minX = std::max(0, minX);
        minY = std::max(0, minY);
        maxX = std::min(this->renderer->winWidth, maxX);
        maxY = std::min(this->renderer->winHeight, maxY);

        float area = triangle->area();

        // Нечего рисовать если площадь 0
        if (area < 0) {
            return;
        }
        float invertArea = 1.0f / area;

        for (int y = minY; y <= maxY; y++) {
            for (int x = minX; x <= maxX; x++) {
                Vector3 p = {x + 0.5f, y + 0.5f, 0};
                auto [w0,w1,w2] = triangle->ComputeBarycentric(p);

                // доп оптимизация чтоб абстрагироваться от того в какую сторону повернуты треугольники
                // (разные повороты разные знаки в барицентрическ координатах имеют)
                w0 *= invertArea;
                w1 *= invertArea;
                w2 *= invertArea;

                // zbuffer магия
                float z =
                        w0 * triangle->v0.position.z +
                        w1 * triangle->v1.position.z +
                        w2 * triangle->v2.position.z;

                int index = y * renderer->winWidth + x;

                if ((w0 >= 0 && w1 >= 0 && w2 >= 0) || (w0 <= 0 && w1 <= 0 && w2 <= 0))
                    // z-buffer sort
                    if (z < zBuffer[index]) {
                        zBuffer[index] = z;
                        this->renderer->DrawPixel(x, y, rColor, gColor, bColor);
                    }
            }
        }
    }
};


#endif //RENDERER_RASTERIZER_HPP
