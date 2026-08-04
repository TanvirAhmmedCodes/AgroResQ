#include "FamilyService.h"

namespace AgroResQ
{
    namespace Services
    {
        FamilyService::FamilyService() = default;

        bool FamilyService::addFamily(const std::string& headName, const std::string& address,
                                      const std::string& contact, int memberCount, bool isDisplaced)
        {
            if (headName.empty() || address.empty() || contact.empty() || memberCount <= 0)
                return false;

            int id = idGenerator.generateNextId("database/families.txt");
            Entities::Family family(id, headName, address, contact, memberCount, isDisplaced);
            return familyRepository.add(family);
        }

        bool FamilyService::updateFamily(int id, const std::string& headName, const std::string& address,
                                         const std::string& contact, int memberCount, bool isDisplaced)
        {
            if (headName.empty() || address.empty() || contact.empty() || memberCount <= 0)
                return false;

            Entities::Family family(id, headName, address, contact, memberCount, isDisplaced);
            return familyRepository.update(family);
        }

        bool FamilyService::deleteFamily(int id)
        {
            return familyRepository.remove(id);
        }

        bool FamilyService::searchFamily(int id, Entities::Family& family)
        {
            return familyRepository.getById(id, family);
        }

        std::vector<Entities::Family> FamilyService::getAllFamilies()
        {
            return familyRepository.getAll();
        }

        std::vector<Entities::Family> FamilyService::getDisplacedFamilies()
        {
            return familyRepository.getDisplacedFamilies();
        }
    }
}