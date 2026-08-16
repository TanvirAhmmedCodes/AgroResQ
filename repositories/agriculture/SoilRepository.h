#pragma once
#include <string>
#include <vector>
#include "../../core/FileManager.h"
#include "../../entities/Soil.h"
#include "../../database/IndexedDB.h"

namespace AgroResQ
{
    namespace Repositories
    {
        class SoilRepository
        {
        private:
            Core::FileManager fileManager;
            std::string filePath;
            Database::IndexedDB<int, Entities::Soil> soilCache;

            Entities::Soil parse(const std::string& line) const;
            void rebuildCache();

        public:
            SoilRepository();
            bool add(const Entities::Soil& soil);
            bool update(const Entities::Soil& soil);
            bool remove(int id);
            bool getById(int id, Entities::Soil& soil);
            std::vector<Entities::Soil> getAll();
            std::vector<Entities::Soil> getByTenant(const std::string& tenantId);
        };
    }
}