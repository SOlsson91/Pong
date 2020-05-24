#include "./Paddle.h"

Paddle::Paddle(int x, int y, int width, int height)
    : rect({x, y , width, height})
{
}

void Paddle::Move(int y)
{
    this->rect.y += y;
}

const SDL_Rect* Paddle::GetRect()
{
    return &this->rect;
}
