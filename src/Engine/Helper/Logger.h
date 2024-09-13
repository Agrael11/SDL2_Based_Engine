#pragma once

#include <string>
#include <format>

namespace Engine::Helper
{
    class Logger
    {
    public:
        enum class Level { Debug, Info, Warning, Error, Fatal };
        enum class ConsoleColor { Black, Red, Green, Yellow, Blue, Magenta, Cyan, White, Reset = -1 };
        
        static void setup(const Level minimumPrintLevel = Level::Info, const Level minimumFileLevel = Level::Warning, const bool printToFile = false, const std::string fileName = "", const bool saveTimedCopy = true, const bool overrideFile = true);

        static void logSimple(const Level level, const std::string_view message);

        template<typename ... Args>
        static void log(const Logger::Level level, const std::string_view message, Args&& ... args)
        {
            if (sizeof...(args) == 0)
            {
                Logger::logSimple(level, message);
            }
            else
            {
                std::string formattedMessage = std::vformat(message, std::make_format_args(args...));
                Logger::logSimple(level, formattedMessage);
            }
        }

    private:
        static std::string returnCurrentTimeDate(const std::string_view format);
        static std::string makeColor(const ConsoleColor color, const bool background, const bool bright);
        static void logConsole(const Level level, const std::string_view message, const std::string_view realTime);
        static void logFile(const Level level, const std::string_view message, const std::string_view realTime);

        static std::string m_fileName;
        static bool m_printToFile;
        static bool m_overrideFile;
        static bool m_openedFile;
        static bool m_saveTimedCopy;
        static std::string m_timedCopyName;
        static Level m_minimumPrintLevel;
        static Level m_minimumFileLevel;
    };
};