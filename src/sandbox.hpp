#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <iostream>

#include "Geometry/Matrix4.hpp"
#include "Geometry/Triangle.hpp"
#include "Rasterizer/Rasterizer.hpp"
#include "Renderer/Renderer.hpp"

class Sandbox {
    Renderer *renderer;
    Rasterizer *rasterizer;

public:
    Sandbox(SDL_Renderer *_renderer, int width, int height) {
        this->renderer = new Renderer(_renderer, width, height);
        this->rasterizer = new Rasterizer(this->renderer);
    }

public:
    // ToDo: после песочницы потереть
    float worldYAngle = 0;

    void HandleKeys(SDL_Event *event) {
        if (event->key.key == SDLK_DOWN) {
            worldYAngle += 3.14 / 45;
        }
        if (event->key.key == SDLK_UP) {
            worldYAngle -= 3.14 / 45;
        }
        // помните пи пополам в периоде? а я помню зачем-то, ну завраппим ч
        if (worldYAngle > 3.14 * 2) {
            worldYAngle = - 3.14 * 2;
        }
        if (worldYAngle < -3.14 * 2) {
            worldYAngle = 3.14 * 2;
        }
        std::cout << worldYAngle << std::endl;
    }
    void Draw() {
        this->renderer->PrepareRender();

        // Базованный (не рендерим, будет полигоном)
        Triangle baseTriangle(
             {200, 200, 0},
             {200, 400, 0},
             {400, 600, 0}
         );


        // Афинное  преобразования на результирующую вьюху, хз запашет нет
        Matrix4 rotationMatrix;
        rotationMatrix.RotationY(worldYAngle);

        // атас, это вьюха результирующая
        Triangle transformed = baseTriangle.TransformTriangle(rotationMatrix);

        Triangle projected = transformed.ProjectTriangle(
            this->renderer->winWidth,
            this->renderer->winHeight/2
            );

        // ну всё
        this->rasterizer->DrawTriangle(&projected);

        this->renderer->FlushAndClear();
    }
};
