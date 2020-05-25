#include "./Ball.h"

Ball::Ball(int x, int y, int w, int h)
    : m_Rect({x, y , w, h}), m_VelX(5), m_VelY(5)
{
}

const SDL_Rect* Ball::GetRect()
{
    return &this->m_Rect;
}

void Ball::Move()
{
    this->m_Rect.x += this->m_VelX;
    this->m_Rect.y += this->m_VelY;
}

int Ball::GetVelX() const
{
    return this->m_VelX;
}

int Ball::GetVelY() const
{
    return this->m_VelY;
}

void Ball::SetVelX(int x)
{
    this->m_VelX = x;
}

void Ball::SetVelY(int y)
{
    this->m_VelY = y;
}

void Ball::ChangePosition(int x, int y)
{
    this->m_Rect.x = x;
    this->m_Rect.y = y;
}
