#pragma once
#include <string>
#include <vector>
#include "../../core/FileManager.h"
#include "../../entities/Volunteer.h"
#include "../../database/IndexedDB.h"

namespace AgroResQ
{
namespace Repositories
{
    class VolunteerRepository
    {
    private:
        Core::FileManager fileManager;
        std::string filePath;
        Database::IndexedDB<int, Entities::Volunteer> volunteerCache;

        Entities::Volunteer parse(const std::string& line) const;
        void rebuildCache();

    public:
        VolunteerRepository();
        bool add(const Entities::Volunteer& volunteer);
        bool update(const Entities::Volunteer& volunteer);
        bool remove(int id);
        bool getById(int id, Entities::Volunteer& volunteer);
        std::vector<Entities::Volunteer> getAll();
        std::vector<Entities::Volunteer> getByTenant(const std::string& tenantId);
        std::vector<Entities::Volunteer> getAvailableVolunteers();
    };
}
}