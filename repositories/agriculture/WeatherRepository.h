#pragma once
#include <string>
#include <vector>
#include "../../core/FileManager.h"
#include "../../entities/Weather.h"
#include "../../database/IndexedDB.h"

namespace AgroResQ
{
namespace Repositories
{
    class WeatherRepository
    {
    private:
        Core::FileManager fileManager;
        std::string filePath;
        Database::IndexedDB<int, Entities::Weather> weatherCache;

        Entities::Weather parse(const std::string& line) const;
        void rebuildCache();

    public:
        WeatherRepository();
        bool add(const Entities::Weather& weather);
        bool update(const Entities::Weather& weather);
        bool remove(int id);
        bool getById(int id, Entities::Weather& weather);
        std::vector<Entities::Weather> getAll();
        std::vector<Entities::Weather> getByTenant(const std::string& tenantId);
    };
}
}