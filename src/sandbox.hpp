#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <iostream>

#include "Geometry/Matrix4.hpp"
#include "Geometry/Triangle.hpp"
#include "Rasterizer/Cube.hpp"
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
        // помните два пи в периоде? а я помню зачем-то, ну завраппим ч
        if (worldYAngle > 3.14 * 2) {
            worldYAngle = - 3.14 * 2;
        }
        if (worldYAngle < -3.14 * 2) {
            worldYAngle = 3.14 * 2;
        }
    }
    void Draw() {
        this->renderer->PrepareRender();
        this->rasterizer->ClearZBuffer();

        Cube cube;

        // Афинное  преобразования на результирующую вьюху, хз запашет нет
        Matrix4 rotationMatrix;
        rotationMatrix.RotationY(worldYAngle);

        // Рендер кубика (пока такой, сорь, но он в норм месте, растерайзер не знаетт ниче про окно)
        for (Square* square: cube.squares) {
            Triangle transformed = square->first->TransformTriangle(rotationMatrix);
            Triangle projected = transformed.ProjectTriangle(
                this->renderer->winWidth,
                this->renderer->winHeight/2
                );
            this->rasterizer->DrawTriangle(&projected);


            Triangle transformedSec = square->second->TransformTriangle(rotationMatrix);
            Triangle projectedSec = transformedSec.ProjectTriangle(
                this->renderer->winWidth,
                this->renderer->winHeight/2
                );
            this->rasterizer->DrawTriangle(&projectedSec,255,0,255);
        }

        this->renderer->FlushAndClear();
    }
};
