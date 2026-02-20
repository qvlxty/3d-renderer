//
// Created by Igor on 20.02.2026.
//

#include "Renderer.hpp"

void Renderer::DrawLine(Vector2 *start, Vector2 *end) {
    // DDA наш братишка, брезенхем сосатб
    auto dVec = *end - *start;

    int steps = abs(dVec.x) > abs(dVec.y) ? abs(dVec.x) : abs(dVec.y);

    float Xinc = dVec.x / (float) steps;
    float Yinc = dVec.y / (float) steps;

    Vector2 *iterVec = new Vector2(start->x, start->y);
    for (int i = 0; i <= steps; i++) {
        this->DrawPixel(round(iterVec->x), round(iterVec->y));
        iterVec->x += Xinc;
        iterVec->y += Yinc;
    }
    delete iterVec;
}

void Renderer::DrawPixel(int x, int y, int colorR, int colorG, int colorB) const {
    if (x >= this->winWidth || x < 0 || y >= this->winHeight || y < 0) {
        return;
    }
    const SDL_PixelFormatDetails *details = SDL_GetPixelFormatDetails(SDL_PIXELFORMAT_ARGB8888);

    uint32_t specificColor = SDL_MapRGB(details,NULL, colorR, colorG, colorB);
    pixelBuffer[y * (pitch / 4) + x] = specificColor;
}
