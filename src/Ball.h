#pragma once
#include <SDL2/SDL.h>

class Ball
{
private:
    SDL_Rect m_Rect;
    int m_VelX;
    int m_VelY;
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
