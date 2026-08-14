#include "DisasterService.h"
#include "../core/AuthManager.h"
#include "../notification/SmsGateway.h"

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
            std::string tenantId = Core::AuthManager::getCurrentUser().tenantId;

            Entities::Disaster disaster(id, name, type, location, date, severity,
                                        division, district, disasterType, affectedPeople, status, tenantId);

            if (disasterRepository.add(disaster))
            {
                alertSystem.sendDisasterAlert(disaster);

                Notification::SmsGateway sms;
                std::string smsMsg = "Disaster: " + name + " at " + location + ". Severity: " + std::to_string(severity) + "/10";
                sms.sendAlertToAllContacts("DISASTER ALERT", smsMsg);

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

            std::string tenantId = Core::AuthManager::getCurrentUser().tenantId;

            Entities::Disaster disaster(id, name, type, location, date, severity,
                                        division, district, disasterType, affectedPeople, status, tenantId);

            if (severity >= 4 && disasterRepository.update(disaster))
            {
                Notification::SmsGateway sms;
                std::string smsMsg = "CRITICAL UPDATE: " + name + " at " + location + ". Severity: " + std::to_string(severity) + "/10";
                sms.sendAlertToAllContacts("CRITICAL DISASTER UPDATE", smsMsg);
                return true;
            }

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