#pragma once
#include <string>
#include <vector>
#include "../../core/FileManager.h"
#include "../../entities/Crop.h"
#include "../../database/IndexedDB.h"

namespace AgroResQ
{
namespace Repositories
{
    class CropRepository
    {
    private:
        Core::FileManager fileManager;
        std::string filePath;
        Database::IndexedDB<int, Entities::Crop> cropCache;

        Entities::Crop parse(const std::string& line) const;
        void rebuildCache();

    public:
        CropRepository();
        bool add(const Entities::Crop& crop);
        bool update(const Entities::Crop& crop);
        bool remove(int id);
        bool getById(int id, Entities::Crop& crop);
        std::vector<Entities::Crop> getAll();
        std::vector<Entities::Crop> getByTenant(const std::string& tenantId);
    };
}
}