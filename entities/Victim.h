#pragma once
#include <string>
#include "../core/BaseEntity.h"

namespace AgroResQ
{
    namespace Entities
    {
        class Victim : public Core::BaseEntity
        {
        private:
            std::string name;
            int age;
            std::string gender;
            std::string address;
            bool vulnerable;
            int familyId;
            std::string healthStatus;
            bool disabled;
            bool rescued;
            bool reliefReceived;
            bool missing;
            int priorityScore;
            int shelterId;
            std::string tenantId;

        public:
            Victim();
            Victim(int id, const std::string& name, int age, const std::string& gender,
                   const std::string& address, bool vulnerable, int familyId,
                   const std::string& healthStatus, bool disabled, bool rescued,
                   bool reliefReceived, bool missing, int priorityScore,
                   int shelterId, const std::string& tenantId = "");

            // Getters and Setters
            void setName(const std::string& name);
            void setAge(int age);
            void setGender(const std::string& gender);
            void setAddress(const std::string& address);
            void setVulnerable(bool vulnerable);
            void setFamilyId(int familyId);
            void setHealthStatus(const std::string& healthStatus);
            void setDisabled(bool disabled);
            void setRescued(bool rescued);
            void setReliefReceived(bool reliefReceived);
            void setMissing(bool missing);
            void setPriorityScore(int priorityScore);
            void setShelterId(int shelterId);
            void setTenantId(const std::string& tenantId);

            std::string getName() const;
            int getAge() const;
            std::string getGender() const;
            std::string getAddress() const;
            bool isVulnerable() const;
            int getFamilyId() const;
            std::string getHealthStatus() const;
            bool isDisabled() const;
            bool isRescued() const;
            bool hasReliefReceived() const;
            bool isMissing() const;
            int getPriorityScore() const;
            int getShelterId() const;
            std::string getTenantId() const;

            std::string toString() const override;
        };
    }
}