#pragma once
#include <vector>
#include "../core/IDGenerator.h"
#include "../core/Validator.h"
#include "../entities/Family.h"
#include "../repositories/victim/FamilyRepository.h"

namespace AgroResQ
{
    namespace Services
    {
        class FamilyService
        {
        private:
            Repositories::FamilyRepository familyRepository;
            Core::Validator validator;
            Core::IDGenerator idGenerator;

        public:
            FamilyService();

            bool addFamily(const std::string& headName, const std::string& address,
                           const std::string& contact, int memberCount, bool isDisplaced);
            bool updateFamily(int id, const std::string& headName, const std::string& address,
                              const std::string& contact, int memberCount, bool isDisplaced);
            bool deleteFamily(int id);
            bool searchFamily(int id, Entities::Family& family);
            std::vector<Entities::Family> getAllFamilies();
            std::vector<Entities::Family> getDisplacedFamilies();
        };
    }
}