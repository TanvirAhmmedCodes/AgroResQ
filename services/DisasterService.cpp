#include "DisasterService.h"

namespace AgroResQ
{
    namespace Services
    {
        DisasterService::DisasterService() = default;

        bool DisasterService::addDisaster(const std::string& name, const std::string& type,
                                          const std::string& location, const std::string& date, int severity,
                                          int division, int district, int disasterType,
                                          int affectedPeople, int status)
        {
            if (!validator.isValidName(name)) return false;
            if (!validator.isValidName(type)) return false;
            if (!validator.isValidLocation(location)) return false;
            if (!validator.isValidDate(date)) return false;
            if (!validator.isValidSeverity(severity)) return false;

            int id = idGenerator.generateNextId("database/disaster.txt");

            Entities::Disaster disaster(id, name, type, location, date, severity,
                                        division, district, disasterType, affectedPeople, status);

            if (disasterRepository.add(disaster))
            {
                alertSystem.sendDisasterAlert(disaster);
                return true;
            }
            return false;
        }

        bool DisasterService::updateDisaster(int id, const std::string& name, const std::string& type,
                                             const std::string& location, const std::string& date, int severity,
                                             int division, int district, int disasterType,
                                             int affectedPeople, int status)
        {
            if (!validator.isValidName(name)) return false;
            if (!validator.isValidName(type)) return false;
            if (!validator.isValidLocation(location)) return false;
            if (!validator.isValidDate(date)) return false;
            if (!validator.isValidSeverity(severity)) return false;

            Entities::Disaster disaster(id, name, type, location, date, severity,
                                        division, district, disasterType, affectedPeople, status);

            return disasterRepository.update(disaster);
        }

        bool DisasterService::deleteDisaster(int id)
        {
            return disasterRepository.remove(id);
        }

        bool DisasterService::searchDisaster(int id, Entities::Disaster& disaster)
        {
            return disasterRepository.getById(id, disaster);
        }

        std::vector<Entities::Disaster> DisasterService::getAllDisasters()
        {
            return disasterRepository.getAll();
        }
    }
}