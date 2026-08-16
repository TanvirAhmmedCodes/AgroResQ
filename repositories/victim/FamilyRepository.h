#pragma once
#include <vector>
#include <string>
#include "../../entities/Family.h"
#include "../../core/FileManager.h"
#include "../../database/IndexedDB.h"

namespace AgroResQ
{
    namespace Repositories
    {
        class FamilyRepository
        {
        private:
            std::string filePath;
            Core::FileManager fileManager;
            Database::IndexedDB<int, Entities::Family> familyCache;

            Entities::Family parse(const std::string& line);
            std::string serialize(const Entities::Family& family);
            void rebuildCache();

        public:
            FamilyRepository();
            bool add(const Entities::Family& family);
            std::vector<Entities::Family> getAll();
            bool getById(int id, Entities::Family& family);
            bool update(const Entities::Family& family);
            bool remove(int id);
            std::vector<Entities::Family> getDisplacedFamilies();
            std::vector<Entities::Family> getByTenant(const std::string& tenantId);
        };
    }
}