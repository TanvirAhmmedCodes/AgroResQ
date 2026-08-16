#pragma once
#include <string>
#include <vector>
#include "../../core/FileManager.h"
#include "../../entities/RescueTeam.h"
#include "../../database/IndexedDB.h"

namespace AgroResQ
{
namespace Repositories
{
    class RescueTeamRepository
    {
    private:
        Core::FileManager fileManager;
        std::string filePath;
        Database::IndexedDB<int, Entities::RescueTeam> teamCache;

        Entities::RescueTeam parse(const std::string& line) const;
        void rebuildCache();

    public:
        RescueTeamRepository();
        bool add(const Entities::RescueTeam& team);
        bool update(const Entities::RescueTeam& team);
        bool remove(int id);
        bool getById(int id, Entities::RescueTeam& team);
        std::vector<Entities::RescueTeam> getAll();
        std::vector<Entities::RescueTeam> getByTenant(const std::string& tenantId);
    };
}
}