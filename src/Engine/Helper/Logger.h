#pragma once

#include <iostream>
#include "StringHelp.h"

namespace Engine::Helper::Logger
{
    enum Level {Debug, Info, Warning, Error, Fatal};
    enum ConsoleColor {Black, Red, Green, Yellow, Blue, Magenta, Cyan, White, Reset = -1};
    
    extern std::string FileName;
    extern bool PrintToFile;
    extern bool OverrideFile;
    extern bool OpenedFile;
    extern bool SaveTimedCopy;
    extern std::string TimedCopyName;
    extern Level MinimumPrintLevel;
    extern Level MinimumFileLevel;
    
    std::string MakeColor(ConsoleColor color, bool background, bool bright);

    void LogSimple(Level level, std::string message);

    template<typename ... Args>
    void Log(Logger::Level level, std::string message, Args ... args)
    {
        if (sizeof...(args) == 0)
        {
            Logger::LogSimple(level, message);
        }
        else
        {
            std::string formattedMessage = string_format(message.c_str(), args...);
            Logger::LogSimple(level, formattedMessage);
        }
    }
};