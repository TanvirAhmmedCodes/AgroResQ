#pragma once
#include "../repositories/disaster/ReliefRepository.h"
#include "../repositories/victim/VictimRepository.h"
#include "../entities/ReliefResource.h"

namespace AgroResQ
{
    namespace Algorithms
    {
        class BudgetCalculator
        {
        private:
            Repositories::ReliefRepository reliefRepository;
            Repositories::VictimRepository victimRepository;

            double getResourceCost(const std::string& category);

        public:
            BudgetCalculator();

            double calculateTotalBudget();
            double calculateBudgetPerVictim();
            std::string generateBudgetReport();
        };
    }
}