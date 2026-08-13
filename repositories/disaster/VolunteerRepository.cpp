#include "VolunteerRepository.h"
#include <fstream>
#include <sstream>

namespace AgroResQ
{
    namespace Repositories
    {
        VolunteerRepository::VolunteerRepository()
        {
            filePath = "database/volunteers.txt";
        }

        std::string VolunteerRepository::serialize(const Entities::Volunteer& volunteer)
        {
            return volunteer.toString();
        }

        Entities::Volunteer VolunteerRepository::parse(const std::string& line)
        {
            std::stringstream ss(line);
            std::string id, name, skill, location, contact, available;

            getline(ss, id, ',');
            getline(ss, name, ',');
            getline(ss, skill, ',');
            getline(ss, location, ',');
            getline(ss, contact, ',');
            getline(ss, available);

            return Entities::Volunteer(
                std::stoi(id), name, skill, location, contact, available == "1"
            );
        }

        bool VolunteerRepository::add(const Entities::Volunteer& volunteer)
        {
            std::ofstream file(filePath, std::ios::app);
            if (!file) return false;
            file << serialize(volunteer) << "\n";
            return true;
        }

        std::vector<Entities::Volunteer> VolunteerRepository::getAll()
        {
            std::vector<Entities::Volunteer> volunteers;
            std::ifstream file(filePath);
            if (!file) return volunteers;

            std::string line;
            while (getline(file, line))
            {
                if (!line.empty())
                    volunteers.push_back(parse(line));
            }
            return volunteers;
        }

        bool VolunteerRepository::getById(int id, Entities::Volunteer& volunteer)
        {
            auto volunteers = getAll();
            for (auto& item : volunteers)
            {
                if (item.getId() == id)
                {
                    volunteer = item;
                    return true;
                }
            }
            return false;
        }

        bool VolunteerRepository::update(const Entities::Volunteer& volunteer)
        {
            auto volunteers = getAll();
            bool updated = false;
            for (auto& item : volunteers)
            {
                if (item.getId() == volunteer.getId())
                {
                    item = volunteer;
                    updated = true;
                }
            }
            if (!updated) return false;

            std::ofstream file(filePath);
            for (auto& item : volunteers)
            {
                file << serialize(item) << "\n";
            }
            return true;
        }

        bool VolunteerRepository::remove(int id)
        {
            auto volunteers = getAll();
            bool removed = false;
            std::vector<Entities::Volunteer> updatedList;

            for (auto& item : volunteers)
            {
                if (item.getId() == id)
                {
                    removed = true;
                }
                else
                {
                    updatedList.push_back(item);
                }
            }
            if (!removed) return false;

            std::ofstream file(filePath);
            for (auto& item : updatedList)
            {
                file << serialize(item) << "\n";
            }
            return true;
        }

        std::vector<Entities::Volunteer> VolunteerRepository::getAvailableVolunteers()
        {
            std::vector<Entities::Volunteer> available;
            auto all = getAll();
            for (auto& v : all)
            {
                if (v.isAvailable())
                    available.push_back(v);
            }
            return available;
        }
    }
}