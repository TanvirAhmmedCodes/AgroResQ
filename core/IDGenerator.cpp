#include "IDGenerator.h"

#include <sstream>

namespace AgroResQ
{
namespace Core
{

IDGenerator::IDGenerator() = default;

int IDGenerator::generateNextId(const std::string& filePath)
{
    std::vector<std::string> lines = fileManager.readLines(filePath);

    int maxId = 0;

    for (const std::string& line : lines)
    {
        std::stringstream stream(line);

        std::string idText;

        std::getline(stream, idText, ',');

        try
        {
            int id = std::stoi(idText);

            if (id > maxId)
            {
                maxId = id;
            }
        }
        catch (...)
        {
            // Ignore invalid records
        }
    }

    return maxId + 1;
}

}
}