#pragma once
#include <string>
#include <cstdlib>

namespace AgroResQ
{
namespace Core
{

inline int safeStoi(const std::string& str, int defaultVal = 0)
{
    if (str.empty()) return defaultVal;
    try
    {
        return std::stoi(str);
    }
    catch (...)
    {
        return defaultVal;
    }
}

inline double safeStod(const std::string& str, double defaultVal = 0.0)
{
    if (str.empty()) return defaultVal;
    try
    {
        return std::stod(str);
    }
    catch (...)
    {
        return defaultVal;
    }
}

inline bool safeStob(const std::string& str, bool defaultVal = false)
{
    if (str.empty()) return defaultVal;
    return (str == "1" || str == "true" || str == "TRUE");
}

}
} 