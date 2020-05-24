#include "./Ball.h"

Ball::Ball(int x, int y, int w, int h)
    : rect({x, y , w, h}), velX(5), velY(5)
{
}

const SDL_Rect* Ball::GetRect()
{
    return &this->rect;
}

void Ball::Move()
{
    this->rect.x += this->velX;
    this->rect.y += this->velY;
}

int Ball::GetVelX() const
{
    return this->velX;
}

int Ball::GetVelY() const
{
    return this->velY;
}

void Ball::SetVelX(int x)
{
    this->velX = x;
}

void Ball::SetVelY(int y)
{
    this->velY = y;
}

void Ball::ChangePosition(int x, int y)
{
    this->rect.x = x;
    this->rect.y = y;
}
