#include "Vector2f.h"

#include <cmath>

#include "Vector2.h"

#ifdef USE_SDL2D
#include <SDL.h>
#endif

using namespace Engine::Math;

Vector2f::Vector2f()
{
    this->X = 0;
    this->Y = 0;
}

Vector2f::Vector2f(float x, float y)
{
    this->X = x;
    this->Y = y;
}

float Vector2f::Distance(Vector2f &other)
{
    float a = abs(this->X - other.X);
    float b = abs(this->Y - other.Y);
    return sqrt(a * a + b * b);
}

void Vector2f::Normalize()
{
    float m = GetMagnitude();;
    if (m > 0)
    {
        this->X /= m;
        this->Y /= m;
    }
}

float Vector2f::GetMagnitude()
{
    return sqrt(this->X * this->X + this->Y * this->Y);
}

void Vector2f::SetMagnitude(float magnitude)
{
    this->Normalize();
    this->X *= magnitude;
    this->Y *= magnitude;
}

Vector2 Vector2f::GetVector2()
{
    return Vector2((int)this->X, (int)this->Y);
}

Vector2f Vector2f::operator+ (Vector2f const &other)
{
    return Vector2f(this->X + other.X, this->Y + other.Y);
}

Vector2f Vector2f::operator- (Vector2f const &other)
{
    return Vector2f(this->X - other.X, this->Y - other.Y);
}

Vector2f Vector2f::operator* (float mult)
{
    return Vector2f(this->X * mult, this->Y * mult);
}

Vector2f Vector2f::operator/ (float mult)
{
    return Vector2f(this->X / mult, this->Y / mult);
}

#ifdef USE_SDL2D
SDL_Point Vector2f::GetSDL_Point()
{
    SDL_Point point;
    point.x = (int)this->X;
    point.y = (int)this->Y;
    return point;
}
#endif