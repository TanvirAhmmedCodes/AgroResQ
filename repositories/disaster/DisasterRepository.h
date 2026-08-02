#pragma once

#include <string>
#include <vector>

#include "../../core/FileManager.h"
#include "../../entities/Disaster.h"

namespace AgroResQ
{
namespace Repositories
{

class DisasterRepository
{
private:
    Core::FileManager fileManager;
    std::string filePath;

    Entities::Disaster parse(const std::string& line) const;

public:
    DisasterRepository();

    bool add(const Entities::Disaster& disaster);

    bool update(const Entities::Disaster& disaster);

    bool remove(int id);

    bool getById(
        int id,
        Entities::Disaster& disaster);

    std::vector<Entities::Disaster> getAll();
};

}
}