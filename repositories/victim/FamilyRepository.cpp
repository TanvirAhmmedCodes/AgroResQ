#include "FamilyRepository.h"
#include <fstream>
#include <sstream>

namespace AgroResQ
{
    namespace Repositories
    {
        FamilyRepository::FamilyRepository()
        {
            filePath = "database/families.txt";
        }

        std::string FamilyRepository::serialize(const Entities::Family& family)
        {
            return family.toString();
        }

        Entities::Family FamilyRepository::parse(const std::string& line)
        {
            std::stringstream ss(line);
            std::string id, headName, address, contact, memberCount, displaced;

            getline(ss, id, ',');
            getline(ss, headName, ',');
            getline(ss, address, ',');
            getline(ss, contact, ',');
            getline(ss, memberCount, ',');
            getline(ss, displaced);

            return Entities::Family(
                std::stoi(id),
                headName,
                address,
                contact,
                std::stoi(memberCount),
                displaced == "1"
            );
        }

        bool FamilyRepository::add(const Entities::Family& family)
        {
            std::ofstream file(filePath, std::ios::app);
            if (!file) return false;
            file << serialize(family) << "\n";
            return true;
        }

        std::vector<Entities::Family> FamilyRepository::getAll()
        {
            std::vector<Entities::Family> families;
            std::ifstream file(filePath);
            if (!file) return families;

            std::string line;
            while (getline(file, line))
            {
                if (!line.empty())
                    families.push_back(parse(line));
            }
            return families;
        }

        bool FamilyRepository::getById(int id, Entities::Family& family)
        {
            std::vector<Entities::Family> families = getAll();
            for (std::size_t i = 0; i < families.size(); ++i)
            {
                if (families[i].getId() == id)
                {
                    family = families[i];
                    return true;
                }
            }
            return false;
        }

        bool FamilyRepository::update(const Entities::Family& family)
        {
            std::vector<Entities::Family> families = getAll();
            bool updated = false;

            for (std::size_t i = 0; i < families.size(); ++i)
            {
                if (families[i].getId() == family.getId())
                {
                    families[i] = family;
                    updated = true;
                }
            }

            if (!updated) return false;

            std::ofstream file(filePath);
            for (std::size_t i = 0; i < families.size(); ++i)
            {
                file << serialize(families[i]) << "\n";
            }
            return true;
        }

        bool FamilyRepository::remove(int id)
        {
            std::vector<Entities::Family> families = getAll();
            bool removed = false;
            std::vector<Entities::Family> updatedList;

            for (std::size_t i = 0; i < families.size(); ++i)
            {
                if (families[i].getId() == id)
                {
                    removed = true;
                }
                else
                {
                    updatedList.push_back(families[i]);
                }
            }

            if (!removed) return false;

            std::ofstream file(filePath);
            for (std::size_t i = 0; i < updatedList.size(); ++i)
            {
                file << serialize(updatedList[i]) << "\n";
            }
            return true;
        }

        std::vector<Entities::Family> FamilyRepository::getDisplacedFamilies()
        {
            std::vector<Entities::Family> displaced;
            std::vector<Entities::Family> all = getAll();

            for (std::size_t i = 0; i < all.size(); ++i)
            {
                if (all[i].isDisplaced())
                {
                    displaced.push_back(all[i]);
                }
            }
            return displaced;
        }
    }
}