#pragma once

#include <string>

#include "FileManager.h"

namespace AgroResQ
{
namespace Core
{

class IDGenerator
{
private:
    FileManager fileManager;

public:
    IDGenerator();

    int generateNextId(const std::string& filePath);
};

}
}