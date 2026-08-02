#pragma once
#include "DisasterMenu.h"
#include "VictimMenu.h"
#include "ReportMenu.h"
#include "AgricultureMenu.h"
#include "ShelterMenu.h"
#include "RescueTeamMenu.h"
#include "ReliefMenu.h"
#include "VolunteerMenu.h"
#include "FamilyMenu.h"
#include "AlertMenu.h"
#include "RouteOptimizationMenu.h"
#include "../services/ReportService.h"
#include "../algorithms/BudgetCalculator.h"

namespace AgroResQ
{
    namespace UI
    {
        class MainMenu
        {
        private:
            DisasterMenu disasterMenu;
            VictimMenu victimMenu;
            ReportMenu reportMenu;
            AgricultureMenu agricultureMenu;
            ShelterMenu shelterMenu;
            RescueTeamMenu rescueTeamMenu;
            ReliefMenu reliefMenu;
            VolunteerMenu volunteerMenu;
            FamilyMenu familyMenu;
            AlertMenu alertMenu;
            RouteOptimizationMenu routeMenu;
            
            Services::ReportService reportService;
            Algorithms::BudgetCalculator budgetCalculator;

            void showDashboard();
            void showBudgetReport();

        public:
            MainMenu();
            void show();
        };
    }
}