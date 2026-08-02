#include "BudgetCalculator.h"
#include <sstream>

namespace AgroResQ
{
    namespace Algorithms
    {
        BudgetCalculator::BudgetCalculator() = default;

        double BudgetCalculator::getResourceCost(const std::string& category)
        {
            if (category == "Food") return 10.0;
            if (category == "Water") return 5.0;
            if (category == "Medicine") return 25.0;
            if (category == "Clothing") return 15.0;
            if (category == "Shelter") return 50.0;
            return 20.0;
        }

        double BudgetCalculator::calculateTotalBudget()
        {
            auto resources = reliefRepository.getAll();
            double total = 0.0;

            for (auto& resource : resources)
            {
                total += resource.getQuantity() * getResourceCost(resource.getCategory());
            }

            return total;
        }

        double BudgetCalculator::calculateBudgetPerVictim()
        {
            auto victims = victimRepository.getAll();
            if (victims.empty()) return 0.0;

            double totalBudget = calculateTotalBudget();
            return totalBudget / victims.size();
        }

        std::string BudgetCalculator::generateBudgetReport()
        {
            std::stringstream ss;

            auto resources = reliefRepository.getAll();
            auto victims = victimRepository.getAll();

            ss << "\n========== BUDGET REPORT ==========\n";
            ss << "Total Resources: " << resources.size() << "\n";
            ss << "Total Victims: " << victims.size() << "\n";
            ss << "Total Budget: $" << calculateTotalBudget() << "\n";
            ss << "Budget Per Victim: $" << calculateBudgetPerVictim() << "\n";

            ss << "\n--- Resource Breakdown ---\n";
            for (auto& resource : resources)
            {
                double cost = resource.getQuantity() * getResourceCost(resource.getCategory());
                ss << resource.getName() << " : " << resource.getQuantity()
                   << " " << resource.getUnit() << " = $" << cost << "\n";
            }

            ss << "=====================================\n";
            return ss.str();
        }
    }
}