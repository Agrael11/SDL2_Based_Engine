#pragma once

#include <vector>
#include <string>

namespace Engine::Helper
{
    //Splits string by "splitChar" - returns vector of strings.
    std::vector<std::string> splitString(const std::string_view input, const char splitChar);
};