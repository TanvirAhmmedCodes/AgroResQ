#pragma once
#include <vector>
#include <string>
#include "../../entities/Volunteer.h"
#include "../../core/FileManager.h"

namespace AgroResQ
{
    namespace Repositories
    {
        class VolunteerRepository
        {
        private:
            std::string filePath;
            Core::FileManager fileManager;

            Entities::Volunteer parse(const std::string& line);
            std::string serialize(const Entities::Volunteer& volunteer);

        public:
            VolunteerRepository();

            bool add(const Entities::Volunteer& volunteer);
            std::vector<Entities::Volunteer> getAll();
            bool getById(int id, Entities::Volunteer& volunteer);
            bool update(const Entities::Volunteer& volunteer);
            bool remove(int id);
            std::vector<Entities::Volunteer> getAvailableVolunteers();
        };
    }
}