#pragma once
#include <string>
#include <vector>
#include "../../core/FileManager.h"
#include "../../entities/Report.h"
#include "../../database/IndexedDB.h"

namespace AgroResQ
{
namespace Repositories
{
    class ReportRepository
    {
    private:
        Core::FileManager fileManager;
        std::string filePath;
        Database::IndexedDB<int, Entities::Report> reportCache;

        Entities::Report parse(const std::string& line) const;
        void rebuildCache();

    public:
        ReportRepository();
        bool add(const Entities::Report& report);
        bool update(const Entities::Report& report);
        bool remove(int id);
        bool getById(int id, Entities::Report& report);
        std::vector<Entities::Report> getAll();
        std::vector<Entities::Report> getByTenant(const std::string& tenantId);
    };
}
}