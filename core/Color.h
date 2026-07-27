#pragma once
#include <string>

#ifdef _WIN32
    #include <windows.h>
    #ifndef ENABLE_VIRTUAL_TERMINAL_PROCESSING
        #define ENABLE_VIRTUAL_TERMINAL_PROCESSING 0x0004
    #endif
#endif

namespace AgroResQ
{
    namespace Core
    {
        class Color
        {
        public:
            
            static std::string reset() { return "\033[0m"; }
            
           
            static std::string black()   { return "\033[30m"; }
            static std::string red()     { return "\033[31m"; }
            static std::string green()   { return "\033[32m"; }
            static std::string yellow()  { return "\033[33m"; }
            static std::string blue()    { return "\033[34m"; }
            static std::string magenta() { return "\033[35m"; }
            static std::string cyan()    { return "\033[36m"; }
            static std::string white()   { return "\033[37m"; }
            
            
            static std::string bold()       { return "\033[1m"; }
            static std::string boldRed()    { return "\033[1;31m"; }
            static std::string boldGreen()  { return "\033[1;32m"; }
            static std::string boldYellow() { return "\033[1;33m"; }
            static std::string boldBlue()   { return "\033[1;34m"; }
            static std::string boldCyan()   { return "\033[1;36m"; }
            
           
            static std::string bgRed()    { return "\033[41m"; }
            static std::string bgGreen()  { return "\033[42m"; }
            static std::string bgYellow() { return "\033[43m"; }
            static std::string bgBlue()   { return "\033[44m"; }
            
            
            static void enableWindowsColors()
            {
                #ifdef _WIN32
                    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
                    if (hOut == INVALID_HANDLE_VALUE) return;
                    
                    DWORD dwMode = 0;
                    if (!GetConsoleMode(hOut, &dwMode)) return;
                    
                    
                    dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
                    SetConsoleMode(hOut, dwMode);
                #endif
            }
            
            
            static bool supportsColor()
            {
                #ifdef _WIN32
                    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
                    if (hOut == INVALID_HANDLE_VALUE) return false;
                    
                    DWORD dwMode = 0;
                    if (!GetConsoleMode(hOut, &dwMode)) return false;
                    
                    return (dwMode & ENABLE_VIRTUAL_TERMINAL_PROCESSING) != 0;
                #else
                    return true;
                #endif
            }
        };
    }
}