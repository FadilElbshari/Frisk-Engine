#pragma once

#include <iostream>

namespace Frisk
{
    namespace Log
    {

        template <typename... Args> void Info(const Args &...to_print)
        {
            std::cout << "\x1b[32m" << "[Info] ";
            ((std::cout << to_print), ...);
            std::cout << "\x1b[0m";
        }

        template <typename... Args> void Warn(const Args &...to_print)
        {
            std::cout << "\x1b[32m" << "[Info] ";
            ((std::cout << to_print), ...);
            std::cout << "\x1b[0m";
        }

        template <typename... Args> void Error(const Args &...to_print)
        {
            std::cout << "\033[31m" << "[Error] ";
            ((std::cout << to_print), ...);
            std::cout << "\033[0m";
        }
    } // namespace Log
} // namespace Frisk
