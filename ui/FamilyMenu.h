#pragma once
#include "../services/FamilyService.h"

namespace AgroResQ
{
    namespace UI
    {
        class FamilyMenu
        {
        private:
            Services::FamilyService familyService;

            void addFamily();
            void viewAllFamilies();
            void searchFamily();
            void updateFamily();
            void deleteFamily();
            void viewDisplacedFamilies();

        public:
            FamilyMenu();
            void show();
        };
    }
}