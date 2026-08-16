#pragma once
#include <string>
#include <windows.h>

#ifndef ENABLE_VIRTUAL_TERMINAL_PROCESSING
#define ENABLE_VIRTUAL_TERMINAL_PROCESSING 0x0004
#endif

namespace AgroResQ
{
    namespace Core
    {
        class Color
        {
        private:
            static bool colorsEnabled; 

            static void ensureEnabled()
            {
                if (!colorsEnabled)
                {
                    enableWindowsColors();
                }
            }

        public:
            static void enableWindowsColors()
            {
                HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
                if (hOut == INVALID_HANDLE_VALUE) return;

                DWORD dwMode = 0;
                if (!GetConsoleMode(hOut, &dwMode)) return;

                dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
                if (SetConsoleMode(hOut, dwMode))
                {
                    colorsEnabled = true;
                }
                else
                {
                    colorsEnabled = false;
                }
            }

            static std::string reset()
            {
                ensureEnabled();
                return colorsEnabled ? "\033[0m" : "";
            }

            static std::string red()
            {
                ensureEnabled();
                return colorsEnabled ? "\033[31m" : "";
            }

            static std::string green()
            {
                ensureEnabled();
                return colorsEnabled ? "\033[32m" : "";
            }

            static std::string yellow()
            {
                ensureEnabled();
                return colorsEnabled ? "\033[33m" : "";
            }

            static std::string blue()
            {
                ensureEnabled();
                return colorsEnabled ? "\033[34m" : "";
            }

            static std::string magenta()
            {
                ensureEnabled();
                return colorsEnabled ? "\033[35m" : "";
            }

            static std::string cyan()
            {
                ensureEnabled();
                return colorsEnabled ? "\033[36m" : "";
            }

            static std::string white()
            {
                ensureEnabled();
                return colorsEnabled ? "\033[37m" : "";
            }

            static std::string bold()
            {
                ensureEnabled();
                return colorsEnabled ? "\033[1m" : "";
            }

            static std::string boldRed()
            {
                ensureEnabled();
                return colorsEnabled ? "\033[1;31m" : "";
            }

            static std::string boldGreen()
            {
                ensureEnabled();
                return colorsEnabled ? "\033[1;32m" : "";
            }

            static std::string boldYellow()
            {
                ensureEnabled();
                return colorsEnabled ? "\033[1;33m" : "";
            }

            static std::string boldBlue()
            {
                ensureEnabled();
                return colorsEnabled ? "\033[1;34m" : "";
            }

            static std::string boldCyan()
            {
                ensureEnabled();
                return colorsEnabled ? "\033[1;36m" : "";
            }

            static std::string bgRed()
            {
                ensureEnabled();
                return colorsEnabled ? "\033[41m" : "";
            }

            static std::string bgGreen()
            {
                ensureEnabled();
                return colorsEnabled ? "\033[42m" : "";
            }

            static std::string bgYellow()
            {
                ensureEnabled();
                return colorsEnabled ? "\033[43m" : "";
            }

            static std::string bgBlue()
            {
                ensureEnabled();
                return colorsEnabled ? "\033[44m" : "";
            }
        };
    }
}