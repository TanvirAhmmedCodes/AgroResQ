#pragma once
#include <vector>
#include "../core/IDGenerator.h"
#include "../core/Validator.h"
#include "../entities/Volunteer.h"
#include "../repositories/disaster/VolunteerRepository.h"

namespace AgroResQ
{
    namespace Services
    {
        class VolunteerService
        {
        private:
            Repositories::VolunteerRepository volunteerRepository;
            Core::Validator validator;
            Core::IDGenerator idGenerator;

        public:
            VolunteerService();

            bool addVolunteer(const std::string& name, const std::string& skill,
                              const std::string& location, const std::string& contact, bool available);
            bool updateVolunteer(int id, const std::string& name, const std::string& skill,
                                 const std::string& location, const std::string& contact, bool available);
            bool deleteVolunteer(int id);
            bool searchVolunteer(int id, Entities::Volunteer& volunteer);
            std::vector<Entities::Volunteer> getAllVolunteers();
            std::vector<Entities::Volunteer> getAvailableVolunteers();
            bool assignTask(int volunteerId, const std::string& task);
        };
    }
}