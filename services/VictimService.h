#pragma once
#include <vector>
#include "../core/IDGenerator.h"
#include "../algorithms/PriorityCalculator.h"
#include "../algorithms/ShelterAllocator.h"
#include "../algorithms/ReliefDistributor.h"
#include "../algorithms/AlertSystem.h"
#include "../entities/Victim.h"
#include "../repositories/victim/VictimRepository.h"

namespace AgroResQ
{
    namespace Services
    {
        class VictimService
        {
        private:
            Repositories::VictimRepository victimRepository;
            Core::IDGenerator idGenerator;
            Algorithms::PriorityCalculator priorityCalculator;
            Algorithms::ShelterAllocator shelterAllocator;
            Algorithms::ReliefDistributor reliefDistributor;
            Algorithms::AlertSystem alertSystem;

        public:
            VictimService();

            bool addVictim(const std::string& name, int age, const std::string& gender,
                           const std::string& address, bool vulnerable, int familyId,
                           const std::string& healthStatus, bool disabled, bool rescued,
                           bool reliefReceived, bool missing, int priorityScore, int shelterId);
            bool assignShelter(int victimId, int shelterId);
            bool updateVictim(int id, const std::string& name, int age, const std::string& gender,
                              const std::string& address, bool vulnerable, int familyId,
                              const std::string& healthStatus, bool disabled, bool rescued,
                              bool reliefReceived, bool missing, int priorityScore, int shelterId);
            bool deleteVictim(int id);
            bool searchVictim(int id, Entities::Victim& victim);
            std::vector<Entities::Victim> getAllVictims();
            std::vector<Entities::Victim> getVictimsByFamily(int familyId);
            std::vector<Entities::Victim> getMissingVictims();
        };
    }
}