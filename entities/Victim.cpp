#include "Victim.h"
#include <sstream>

namespace AgroResQ
{
    namespace Entities
    {
        Victim::Victim()
            : age(0), vulnerable(false), familyId(0), healthStatus("Healthy"),
              disabled(false), rescued(false), reliefReceived(false),
              missing(false), priorityScore(0), shelterId(0) {}

        Victim::Victim(int id, const std::string& name, int age, const std::string& gender,
                       const std::string& address, bool vulnerable, int familyId,
                       const std::string& healthStatus, bool disabled, bool rescued,
                       bool reliefReceived, bool missing, int priorityScore,
                       int shelterId, const std::string& tenantId)
        {
            setId(id);
            this->name = name;
            this->age = age;
            this->gender = gender;
            this->address = address;
            this->vulnerable = vulnerable;
            this->familyId = familyId;
            this->healthStatus = healthStatus;
            this->disabled = disabled;
            this->rescued = rescued;
            this->reliefReceived = reliefReceived;
            this->missing = missing;
            this->priorityScore = priorityScore;
            this->shelterId = shelterId;
            this->tenantId = tenantId;
        }

        void Victim::setName(const std::string& name) { this->name = name; }
        void Victim::setAge(int age) { this->age = age; }
        void Victim::setGender(const std::string& gender) { this->gender = gender; }
        void Victim::setAddress(const std::string& address) { this->address = address; }
        void Victim::setVulnerable(bool vulnerable) { this->vulnerable = vulnerable; }
        void Victim::setFamilyId(int familyId) { this->familyId = familyId; }
        void Victim::setHealthStatus(const std::string& healthStatus) { this->healthStatus = healthStatus; }
        void Victim::setDisabled(bool disabled) { this->disabled = disabled; }
        void Victim::setRescued(bool rescued) { this->rescued = rescued; }
        void Victim::setReliefReceived(bool reliefReceived) { this->reliefReceived = reliefReceived; }
        void Victim::setMissing(bool missing) { this->missing = missing; }
        void Victim::setPriorityScore(int priorityScore) { this->priorityScore = priorityScore; }
        void Victim::setShelterId(int shelterId) { this->shelterId = shelterId; }
        void Victim::setTenantId(const std::string& tenantId) { this->tenantId = tenantId; }

        std::string Victim::getName() const { return name; }
        int Victim::getAge() const { return age; }
        std::string Victim::getGender() const { return gender; }
        std::string Victim::getAddress() const { return address; }
        bool Victim::isVulnerable() const { return vulnerable; }
        int Victim::getFamilyId() const { return familyId; }
        std::string Victim::getHealthStatus() const { return healthStatus; }
        bool Victim::isDisabled() const { return disabled; }
        bool Victim::isRescued() const { return rescued; }
        bool Victim::hasReliefReceived() const { return reliefReceived; }
        bool Victim::isMissing() const { return missing; }
        int Victim::getPriorityScore() const { return priorityScore; }
        int Victim::getShelterId() const { return shelterId; }
        std::string Victim::getTenantId() const { return tenantId; }

        std::string Victim::toString() const
        {
            std::stringstream stream;
            stream << getId() << "," << name << "," << age << "," << gender << ","
                   << address << "," << vulnerable << "," << familyId << ","
                   << healthStatus << "," << disabled << "," << rescued << ","
                   << reliefReceived << "," << missing << "," << priorityScore << ","
                   << shelterId << "," << tenantId;
            return stream.str();
        }
    }
}