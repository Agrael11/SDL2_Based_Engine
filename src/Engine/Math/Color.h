#pragma once

namespace Engine::Math
{
    class Colorf;
    class Color
    {
        public:
        int R;
        int G;
        int B;
        int A;

        Color();
        Color(int r, int g, int b, int a);

        Colorf GetColorf();
    };
};