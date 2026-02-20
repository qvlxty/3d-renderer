//
// Created by Igor on 20.02.2026.
//
#ifndef RENDERER_RENDERER_HPP
#define RENDERER_RENDERER_HPP

#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include "../geometry/Vector2.hpp"
#include <iostream>

class Renderer {
public:
    void *pixels;
    int pitch;
    SDL_Texture *texture;
    uint32_t *pixelBuffer;
    SDL_Renderer *renderer;

    int winWidth;
    int winHeight;

public:
    Renderer(SDL_Renderer *renderer, int width, int height) {
        this->winHeight = height;
        this->winWidth = width;
        this->renderer = renderer;
        texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING, width, height);
    }

    void PrepareRender() {
        bool success = SDL_LockTexture(texture, NULL, &pixels, &pitch);
        if (!success) {
            return;
        }
        pixelBuffer = (uint32_t *) pixels;
    }

    void FlushAndClear() {
        SDL_UnlockTexture(texture);
        SDL_RenderClear(renderer);
        SDL_RenderTexture(renderer, texture, NULL, NULL);
        SDL_RenderPresent(renderer);
    }


    void DrawLine(Vector2 *start, Vector2 *end);
    void DrawPixel(int x, int y, int colorR = 255, int colorG = 128, int colorB = 0) const;
};


#endif //RENDERER_RENDERER_HPP
