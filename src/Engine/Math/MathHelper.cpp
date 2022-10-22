#include "MathHelper.h"

using namespace Engine::Math;

double MathHelper::PI = 3.1415926535897932384626433832795028841971693993751058209749445923078164062;
float MathHelper::PIf = 3.1415926535897932384626433832795028841971693993751058209749445923078164062f;
double MathHelper::TAU = 6.2831853071795864769252867665590057683943387987502116419498891846156328125;
float MathHelper::TAUf = 6.2831853071795864769252867665590057683943387987502116419498891846156328125f;


float MathHelper::DegToRad(float degrees)
{
    return degrees * (MathHelper::PIf / 180.f);
}

double MathHelper::DegToRad(double degrees)
{
    return degrees * (MathHelper::PI / 180.0);
}

float MathHelper::RadToDeg(float radians)
{
    return radians * (180.f / MathHelper::PIf);
}

double MathHelper::RadToDeg(double radians)
{
    return radians * (180.0 / MathHelper::PI);
}
