#pragma once
#include <string>
#include <vector>
#include "../../core/FileManager.h"
#include "../../entities/Report.h"

namespace AgroResQ
{
namespace Repositories
{
    class ReportRepository
    {
    private:
        Core::FileManager fileManager;
        std::string filePath;
        Entities::Report parse(const std::string& line) const;

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