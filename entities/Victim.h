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

        public:
            Victim();

            Victim(
                int id,
                const std::string &name,
                int age,
                const std::string &gender,
                const std::string &address,
                bool vulnerable,
                int familyId,
                const std::string &healthStatus,
                bool disabled,
                bool rescued,
                bool reliefReceived,
                bool missing,
                int priorityScore,
                int shelterId);

            void setName(
                const std::string &name);

            void setAge(
                int age);

            void setGender(
                const std::string &gender);

            void setAddress(
                const std::string &address);

            void setVulnerable(
                bool vulnerable);

            std::string getName() const;

            int getAge() const;

            std::string getGender() const;

            std::string getAddress() const;

            bool isVulnerable() const;
            int getFamilyId() const;
            void setFamilyId(int familyId);

            std::string getHealthStatus() const;
            void setHealthStatus(const std::string &healthStatus);

            bool isDisabled() const;
            void setDisabled(bool disabled);

            bool isRescued() const;
            void setRescued(bool rescued);

            bool hasReliefReceived() const;
            void setReliefReceived(bool reliefReceived);

            bool isMissing() const;
            void setMissing(bool missing);

            int getPriorityScore() const;
            void setPriorityScore(int priorityScore);

            int getShelterId() const;
            void setShelterId(int shelterId);

            std::string toString() const;
        };

    }
}