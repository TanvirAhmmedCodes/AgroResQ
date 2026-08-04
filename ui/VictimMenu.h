#pragma once
#include "../services/VictimService.h"
#include "../data_structures/PriorityQueue.h"

namespace AgroResQ
{
    namespace UI
    {
        class VictimMenu
        {
        private:
            Services::VictimService victimService;
            DataStructures::PriorityQueue<int> rescueQueue;

            void addVictim();
            void viewAllVictims();
            void searchVictim();
            void updateVictim();
            void deleteVictim();
            void searchFamily();
            void viewMissingVictims();
            void assignShelter();
            void processNextRescue();

        public:
            VictimMenu();
            void show();
        };
    }
}