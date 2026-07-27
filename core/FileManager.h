#pragma once

#include <string>
#include <vector>

namespace AgroResQ
{
namespace Core
{

class FileManager
{
public:
    FileManager();

    bool createFile(const std::string& filePath);

    bool writeFile(
        const std::string& filePath,
        const std::string& data);

    bool appendFile(
        const std::string& filePath,
        const std::string& data);

    std::string readFile(
        const std::string& filePath) const;

    std::vector<std::string> readLines(
        const std::string& filePath) const;

    bool deleteFile(
        const std::string& filePath) const;

    bool fileExists(
        const std::string& filePath) const;
};

}
}