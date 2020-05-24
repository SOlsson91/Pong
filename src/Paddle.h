#pragma once
#include <SDL2/SDL.h>

class Paddle
{
private:
    SDL_Rect rect;
public:
    Paddle(int x, int y, int width, int height);
    void Move(int y);
    const SDL_Rect* GetRect();
};
