#include "VolunteerService.h"

namespace AgroResQ
{
    namespace Services
    {
        VolunteerService::VolunteerService() = default;

        bool VolunteerService::addVolunteer(const std::string& name, const std::string& skill,
                                            const std::string& location, const std::string& contact, bool available)
        {
            if (name.empty() || skill.empty() || location.empty() || contact.empty())
                return false;

            int id = idGenerator.generateNextId("database/volunteers.txt");
            Entities::Volunteer volunteer(id, name, skill, location, contact, available);
            return volunteerRepository.add(volunteer);
        }

        bool VolunteerService::updateVolunteer(int id, const std::string& name, const std::string& skill,
                                               const std::string& location, const std::string& contact, bool available)
        {
            if (name.empty() || skill.empty() || location.empty() || contact.empty())
                return false;

            Entities::Volunteer volunteer(id, name, skill, location, contact, available);
            return volunteerRepository.update(volunteer);
        }

        bool VolunteerService::deleteVolunteer(int id)
        {
            return volunteerRepository.remove(id);
        }

        bool VolunteerService::searchVolunteer(int id, Entities::Volunteer& volunteer)
        {
            return volunteerRepository.getById(id, volunteer);
        }

        std::vector<Entities::Volunteer> VolunteerService::getAllVolunteers()
        {
            return volunteerRepository.getAll();
        }

        std::vector<Entities::Volunteer> VolunteerService::getAvailableVolunteers()
        {
            return volunteerRepository.getAvailableVolunteers();
        }

        bool VolunteerService::assignTask(int volunteerId, const std::string& task)
        {
            Entities::Volunteer volunteer;
            if (!volunteerRepository.getById(volunteerId, volunteer))
                return false;

            if (!volunteer.isAvailable())
                return false;

            volunteer.setAvailable(false);
            return volunteerRepository.update(volunteer);
        }
    }
}