#include "StringHelp.h"

#include <vector>
#include <string>
#include <iostream>

std::vector<std::string> Engine::Helper::splitString(const std::string_view input, const char splitChar)
{
    std::vector<std::string> tokens;
    std::string token;

    for (char c : input)
    {
        if (c == splitChar)
        {
            if (!token.empty())
            {
                tokens.push_back(std::move(token));
                token.clear();
            }
        }
        else
        {
            token += c;
        }
    }

    if (!token.empty())
    {
        tokens.push_back(std::move(token));
    }

    return tokens;
}