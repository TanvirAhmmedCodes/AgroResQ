#pragma once
#include <string>
#include <vector>
#include "../../core/FileManager.h"
#include "../../entities/ReliefResource.h"

namespace AgroResQ
{
namespace Repositories
{
    class ReliefRepository
    {
    private:
        Core::FileManager fileManager;
        std::string filePath;
        Entities::ReliefResource parse(const std::string& line) const;

    public:
        ReliefRepository();
        bool add(const Entities::ReliefResource& resource);
        bool update(const Entities::ReliefResource& resource);
        bool remove(int id);
        bool getById(int id, Entities::ReliefResource& resource);
        std::vector<Entities::ReliefResource> getAll();
        std::vector<Entities::ReliefResource> getByTenant(const std::string& tenantId);
    };
}
}