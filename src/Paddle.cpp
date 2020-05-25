#include "./Paddle.h"

Paddle::Paddle(int x, int y, int width, int height)
    : m_Rect({x, y , width, height})
{
}

void Paddle::Move(int y)
{
    this->m_Rect.y += y;
}

const SDL_Rect* Paddle::GetRect()
{
    return &this->m_Rect;
}
