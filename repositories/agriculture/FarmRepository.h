#pragma once
#include <string>
#include <vector>
#include "../../core/FileManager.h"
#include "../../entities/Farm.h"

namespace AgroResQ
{
namespace Repositories
{
    class FarmRepository
    {
    private:
        Core::FileManager fileManager;
        std::string filePath;
        Entities::Farm parse(const std::string& line) const;

    public:
        FarmRepository();
        bool add(const Entities::Farm& farm);
        bool update(const Entities::Farm& farm);
        bool remove(int id);
        bool getById(int id, Entities::Farm& farm);
        std::vector<Entities::Farm> getAll();
        std::vector<Entities::Farm> getByTenant(const std::string& tenantId);
    };
}
}