#include "Color.h"
#include "Colorf.h"

using namespace Engine::Math;

Color::Color()
{
    this->R = 0;
    this->G = 0;
    this->B = 0;
    this->A = 0;
}

Color::Color(int r, int g, int b, int a)
{
    this->R = r;
    this->G = g;
    this->B = b;
    this->A = a;
}

Colorf Color::GetColorf()
{
    return Colorf((float)(this->R/255.0f),(float)(this->G/255.0f),(float)(this->B/255.0f),(float)(this->A/255.0f));
}