#pragma once

#include <vector>
#include <string>

namespace Engine::Helper
{
    class StringHelper
    {
        //Splits string by "splitChar" - returns vector of strings.
        static std::vector<std::string> splitString(const std::string_view input, const char splitChar);
    };
};