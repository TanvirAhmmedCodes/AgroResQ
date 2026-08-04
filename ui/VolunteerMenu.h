#pragma once
#include "../services/VolunteerService.h"

namespace AgroResQ
{
    namespace UI
    {
        class VolunteerMenu
        {
        private:
            Services::VolunteerService volunteerService;

            void addVolunteer();
            void viewAllVolunteers();
            void searchVolunteer();
            void updateVolunteer();
            void deleteVolunteer();
            void viewAvailableVolunteers();
            void assignTask();

        public:
            VolunteerMenu();
            void show();
        };
    }
}