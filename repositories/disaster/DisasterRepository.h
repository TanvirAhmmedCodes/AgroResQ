#pragma once
#include <string>
#include <vector>
#include "../../core/FileManager.h"
#include "../../entities/Disaster.h"
#include "../../database/IndexedDB.h"

namespace AgroResQ
{
namespace Repositories
{
    class DisasterRepository
    {
    private:
        Core::FileManager fileManager;
        std::string filePath;
        Database::IndexedDB<int, Entities::Disaster> disasterCache;  // NEW

        Entities::Disaster parse(const std::string& line) const;
        void rebuildCache();  // NEW

    public:
        DisasterRepository();

        bool add(const Entities::Disaster& disaster);
        bool update(const Entities::Disaster& disaster);
        bool remove(int id);
        bool getById(int id, Entities::Disaster& disaster);
        std::vector<Entities::Disaster> getAll();
        std::vector<Entities::Disaster> getByTenant(const std::string& tenantId);
    };
}
}