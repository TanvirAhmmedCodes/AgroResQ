#pragma once
#include <string>
#include <vector>
#include "../../core/FileManager.h"
#include "../../entities/Shelter.h"
#include "../../database/IndexedDB.h"

namespace AgroResQ
{
namespace Repositories
{
    class ShelterRepository
    {
    private:
        Core::FileManager fileManager;
        std::string filePath;
        Database::IndexedDB<int, Entities::Shelter> shelterCache;  // NEW

        Entities::Shelter parse(const std::string& line) const;
        void rebuildCache();

    public:
        ShelterRepository();

        bool add(const Entities::Shelter& shelter);
        bool update(const Entities::Shelter& shelter);
        bool remove(int id);
        bool getById(int id, Entities::Shelter& shelter);
        std::vector<Entities::Shelter> getAll();
        std::vector<Entities::Shelter> getByTenant(const std::string& tenantId);
    };
}
}