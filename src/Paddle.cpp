#include "Paddle.h"

Paddle::Paddle(int width, int height)
    : width(width), height(height)
{
}

Paddle::~Paddle()
{
}

int Paddle::GetWidth()
{
    return width;
}

int Paddle::GetHeight()
{
    return height;
}
