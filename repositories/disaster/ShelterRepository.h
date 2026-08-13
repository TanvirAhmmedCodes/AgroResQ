#pragma once

#include <vector>
#include <string>

#include "../../entities/Shelter.h"
#include "../../core/FileManager.h"

namespace AgroResQ
{
namespace Repositories
{

class ShelterRepository
{
private:

    std::string filePath;

    Core::FileManager fileManager;

    Entities::Shelter parse(
        const std::string& line);

    std::string serialize(
        const Entities::Shelter& shelter);

public:

    ShelterRepository();

    bool add(
        const Entities::Shelter& shelter);

    std::vector<Entities::Shelter> getAll();

    bool getById(
        int id,
        Entities::Shelter& shelter);

    bool update(
        const Entities::Shelter& shelter);

    bool remove(
        int id);
};

}
}