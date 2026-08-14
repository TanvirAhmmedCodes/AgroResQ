#pragma once
#include <vector>
#include <string>
#include "../../entities/Victim.h"
#include "../../core/FileManager.h"

namespace AgroResQ
{
    namespace Repositories
    {
        class VictimRepository
        {
        private:
            std::string filePath;
            Core::FileManager fileManager;
            Entities::Victim parse(const std::string& line);
            std::string serialize(const Entities::Victim& victim);

        public:
            VictimRepository();
            bool add(const Entities::Victim& victim);
            std::vector<Entities::Victim> getAll();
            bool getById(int id, Entities::Victim& victim);
            bool update(const Entities::Victim& victim);
            bool remove(int id);
            std::vector<Entities::Victim> getByTenant(const std::string& tenantId);
        };
    }
}