#include "Volunteer.h"
#include <sstream>

namespace AgroResQ
{
    namespace Entities
    {
        Volunteer::Volunteer() : available(true) {}

        Volunteer::Volunteer(int id, const std::string& name, const std::string& skill,
                             const std::string& location, const std::string& contact,
                             bool available, const std::string& tenantId)
        {
            setId(id);
            this->name = name;
            this->skill = skill;
            this->location = location;
            this->contact = contact;
            this->available = available;
            this->tenantId = tenantId;
        }

        void Volunteer::setName(const std::string& name) { this->name = name; }
        void Volunteer::setSkill(const std::string& skill) { this->skill = skill; }
        void Volunteer::setLocation(const std::string& location) { this->location = location; }
        void Volunteer::setContact(const std::string& contact) { this->contact = contact; }
        void Volunteer::setAvailable(bool available) { this->available = available; }
        void Volunteer::setTenantId(const std::string& tenantId) { this->tenantId = tenantId; }

        std::string Volunteer::getName() const { return name; }
        std::string Volunteer::getSkill() const { return skill; }
        std::string Volunteer::getLocation() const { return location; }
        std::string Volunteer::getContact() const { return contact; }
        bool Volunteer::isAvailable() const { return available; }
        std::string Volunteer::getTenantId() const { return tenantId; }

        std::string Volunteer::toString() const
        {
            std::stringstream ss;
            ss << getId() << "," << name << "," << skill << ","
               << location << "," << contact << "," << available << ","
               << tenantId;
            return ss.str();
        }
    }
}