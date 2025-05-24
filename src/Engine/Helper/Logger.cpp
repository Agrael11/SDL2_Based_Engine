#ifndef EMSCRIPTEN
#include <fstream>
#else
#include <emscripten.h>
#endif

#include <format>

#include "Logger.h"
#include "StringHelp.h"

namespace Engine::Helper
{
    Logger::Level Logger::m_minimumPrintLevel = Logger::Level::Info;
    Logger::Level Logger::m_minimumFileLevel = Logger::Level::Warning;
    bool Logger::m_printToFile = false;
    bool Logger::m_overrideFile = true;
    bool Logger::m_saveTimedCopy = true;
    bool Logger::m_openedFile = false;
    std::string Logger::m_fileName = "";
    std::string Logger::m_timedCopyName = "";

    void Logger::setup(Level minimumPrintLevel, Level minimumFileLevel, bool printToFile, std::string fileName, bool saveTimedCopy, bool overrideFile)
    {
        m_minimumPrintLevel = minimumPrintLevel;
        m_minimumFileLevel = minimumFileLevel;
        m_printToFile = printToFile;
        m_fileName = fileName;
        m_saveTimedCopy = saveTimedCopy;
        m_overrideFile = overrideFile;
    }

    std::string Logger::returnCurrentTimeDate(const std::string_view format)
    {
        time_t now = time(0);
        struct tm tstruct;
        char buf[80];
#if WIN32
        localtime_s(&tstruct, &now);
#else
        localtime_r(&now, &tstruct);
#endif
        strftime(buf, sizeof(buf), format.data(), &tstruct);
        return buf;
    }

    std::string Logger::makeColor(Logger::ConsoleColor color, bool background, bool bright)
    {
#if EMSCRIPTEN

        return "";

#else

        int col = static_cast<int>(color);

        if (background) col += 40;
        else col += 30;
        if (bright) col += 60;

        if (col == -1) col = 0;

        return std::format("\x1b[{}m", col);

#endif
    }


    void Logger::logSimple(const Logger::Level level, const std::string_view message)
    {
        std::string realTime = returnCurrentTimeDate("%Y-%m-%d %X");
        
        if (level >= m_minimumPrintLevel) logConsole(level, message, realTime);

#ifndef EMSCRIPTEN
        if (m_printToFile && !m_fileName.empty()  && level >= m_minimumFileLevel) logFile(level, message, realTime);
#endif
    }

    void Logger::logConsole(const Logger::Level level, const std::string_view message, const std::string_view realTime)
    {
        std::string gray = makeColor(ConsoleColor::White, false, false);
        std::string blue = makeColor(ConsoleColor::Blue, false, true);

        std::string levelColor;
        std::string levelString;
        switch (level)
        {
        case Level::Debug:
            levelColor = makeColor(ConsoleColor::White, false, true);
            levelString = "Debug";
            break;
        case Level::Info:
            levelColor = makeColor(ConsoleColor::Blue, false, true);
            levelString = "Info";
            break;
        case Level::Warning:
            levelColor = makeColor(ConsoleColor::Yellow, false, true);
            levelString = "Warning";
            break;
        case Level::Error:
            levelColor = makeColor(ConsoleColor::Red, false, true);
            levelString = "Error";
            break;
        default:
        case Level::Fatal:
            levelColor = makeColor(ConsoleColor::Red, false, false);
            levelString = "Fatal Error";
            break;
        }

        printf("[%s%s%s @ %s%s%s] %s\n", levelColor.c_str(), levelString.c_str(), gray.c_str(), blue.c_str(), realTime.data(), gray.c_str(), message.data());
    }

#ifndef EMSCRIPTEN
    void Logger::logFile(const Logger::Level level, const std::string_view message, const std::string_view realTime)
    {
        std::string levelString;
        switch (level)
        {
        case Level::Debug:
            levelString = "Debug";
            break;
        case Level::Info:
            levelString = "Info";
            break;
        case Level::Warning:
            levelString = "Warning";
            break;
        case Level::Error:
            levelString = "Error";
            break;
        default:
        case Level::Fatal:
            levelString = "Fatal Error";
            break;
        }
        
        std::string printText = std::format("[{} @ {}] {}\n", levelString, realTime, message);

        std::ofstream myOutFile(m_fileName, (m_overrideFile && !m_openedFile) ? std::ios_base::trunc : std::ios_base::app);
        if (!myOutFile)
        {
            Logger::logConsole(Logger::Level::Error, std::format("Failed to open Log file: {}", m_fileName), realTime);
            return;
        }

        myOutFile << printText;
        myOutFile.close();

        if (m_saveTimedCopy)
        {
            if (m_timedCopyName == "")
            {
                m_timedCopyName = std::format("{}_{}_{}", returnCurrentTimeDate("%Y-%m-%d"), returnCurrentTimeDate("%H-%M-%S"), m_fileName);
            }
            std::ofstream mySecondOutFile(m_timedCopyName, std::ios_base::app);
            if (!mySecondOutFile)
            {
                Logger::logConsole(Logger::Level::Error, std::format("Failed to open Log file: {}", m_timedCopyName), realTime);
                return;
            }
            mySecondOutFile << printText;
            mySecondOutFile.close();
        }
        m_openedFile = true;
    }
#endif
}