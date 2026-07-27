#pragma once

#include <string>
#include <vector>

#include "../../core/FileManager.h"
#include "../../entities/Soil.h"

namespace AgroResQ
{
namespace Repositories
{

class SoilRepository
{
private:
    Core::FileManager fileManager;
    std::string filePath;

    Entities::Soil parse(const std::string& line) const;

public:
    SoilRepository();

    bool add(const Entities::Soil& soil);

    bool update(const Entities::Soil& soil);

    bool remove(int id);

    bool getById(
        int id,
        Entities::Soil& soil);

    std::vector<Entities::Soil> getAll();
};

}
}