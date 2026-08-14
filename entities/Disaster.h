#pragma once
#include <string>
#include "../core/BaseEntity.h"

namespace AgroResQ
{
    namespace Entities
    {
        class Disaster : public Core::BaseEntity
        {
        private:
            std::string name;
            std::string type;
            std::string location;
            std::string date;
            int severity;
            int division;
            int district;
            int disasterType;
            int affectedPeople;
            int status;
            std::string tenantId;

        public:
            Disaster();
            Disaster(int id, const std::string& name, const std::string& type,
                     const std::string& location, const std::string& date, int severity,
                     int division, int district, int disasterType,
                     int affectedPeople, int status, const std::string& tenantId = "");

            void setName(const std::string& name);
            void setType(const std::string& type);
            void setLocation(const std::string& location);
            void setDate(const std::string& date);
            void setSeverity(int severity);
            void setDivision(int division);
            void setDistrict(int district);
            void setDisasterType(int disasterType);
            void setAffectedPeople(int affectedPeople);
            void setStatus(int status);
            void setTenantId(const std::string& tenantId);

            std::string getName() const;
            std::string getType() const;
            std::string getLocation() const;
            std::string getDate() const;
            int getSeverity() const;
            int getDivision() const;
            int getDistrict() const;
            int getDisasterType() const;
            int getAffectedPeople() const;
            int getStatus() const;
            std::string getTenantId() const;

            std::string getDivisionName() const;
            std::string getDistrictName() const;
            std::string getDisasterTypeName() const;
            std::string getStatusName() const;
            std::string getSeverityName() const;

            std::string toString() const override;
        };
    }
}