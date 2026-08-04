#pragma once
#include <string>
#include "../core/BaseEntity.h"

namespace AgroResQ
{
    namespace Entities
    {
        class Volunteer : public Core::BaseEntity
        {
        private:
            std::string name;
            std::string skill;
            std::string location;
            std::string contact;
            bool available;

        public:
            Volunteer();
            Volunteer(int id, const std::string& name, const std::string& skill,
                      const std::string& location, const std::string& contact, bool available);

            void setName(const std::string& name);
            void setSkill(const std::string& skill);
            void setLocation(const std::string& location);
            void setContact(const std::string& contact);
            void setAvailable(bool available);

            std::string getName() const;
            std::string getSkill() const;
            std::string getLocation() const;
            std::string getContact() const;
            bool isAvailable() const;

            std::string toString() const;
        };
    }
}