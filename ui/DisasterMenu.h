#pragma once
#include "../services/DisasterService.h"

namespace AgroResQ
{
    namespace UI
    {
        class DisasterMenu
        {
        private:
            Services::DisasterService disasterService;

            void addDisaster();
            void viewAllDisasters();
            void searchDisaster();
            void updateDisaster();
            void deleteDisaster();

        public:
            DisasterMenu();
            void show();
        };
    }
}