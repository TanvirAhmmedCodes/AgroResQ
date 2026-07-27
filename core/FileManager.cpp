#include "FileManager.h"

#include <fstream>
#include <cstdio>

namespace AgroResQ
{
namespace Core
{

FileManager::FileManager() = default;

bool FileManager::createFile(const std::string& filePath)
{
    std::ofstream file(filePath, std::ios::app);

    if (!file.is_open())
    {
        return false;
    }

    file.close();
    return true;
}

bool FileManager::writeFile(
    const std::string& filePath,
    const std::string& data)
{
    std::ofstream file(filePath);

    if (!file.is_open())
    {
        return false;
    }

    file << data;

    file.close();

    return true;
}

bool FileManager::appendFile(
    const std::string& filePath,
    const std::string& data)
{
    std::ofstream file(filePath, std::ios::app);

    if (!file.is_open())
    {
        return false;
    }

    file << data;

    file.close();

    return true;
}

std::string FileManager::readFile(
    const std::string& filePath) const
{
    std::ifstream file(filePath);

    if (!file.is_open())
    {
        return "";
    }

    std::string content;
    std::string line;

    while (std::getline(file, line))
    {
        content += line;
        content += '\n';
    }

    file.close();

    return content;
}

std::vector<std::string> FileManager::readLines(
    const std::string& filePath) const
{
    std::vector<std::string> lines;

    std::ifstream file(filePath);

    if (!file.is_open())
    {
        return lines;
    }

    std::string line;

    while (std::getline(file, line))
    {
        if (!line.empty())
        {
            lines.push_back(line);
        }
    }

    file.close();

    return lines;
}

bool FileManager::deleteFile(
    const std::string& filePath) const
{
    return std::remove(filePath.c_str()) == 0;
}

bool FileManager::fileExists(
    const std::string& filePath) const
{
    std::ifstream file(filePath);

    bool exists = file.good();

    file.close();

    return exists;
}

}
}