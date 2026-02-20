#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <iostream>

#include "Geometry/Triangle.hpp"
#include "Geometry/Vector2.hpp"
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
    void Draw() {
        this->renderer->PrepareRender();

        this->renderer->DrawLine(
            new Vector2(0, 0),
            new Vector2(500, 500)
        );

        this->rasterizer->DrawTriangle(
            new Triangle(
                *new Vector2(0, 0),
                *new Vector2(0, 500),
                *new Vector2(500, 0)
            ));

        this->rasterizer->DrawTriangle(
            new Triangle(
                *new Vector2(500, 720),
                *new Vector2(720, 700),
                *new Vector2(500, 0)
            ),255,0,0);

        this->renderer->FlushAndClear();
    }
};
