#pragma once
#include <SDL2/SDL.h>

class Ball
{
private:
    SDL_Rect rect;
    int velX;
    int velY;

public:
    Ball(int x, int y, int width, int height);
    void Move();
    const SDL_Rect* GetRect();
    void ChangePosition(int x, int y);
    int GetVelX() const;
    int GetVelY() const;
    void SetVelX(int x);
    void SetVelY(int y);
};
