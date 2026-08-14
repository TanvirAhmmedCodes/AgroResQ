#pragma once
#include <string>
#include "../core/BaseEntity.h"

namespace AgroResQ
{
    namespace Entities
    {
        class Family : public Core::BaseEntity
        {
        private:
            std::string headName;
            std::string address;
            std::string contact;
            int memberCount;
            bool displaced;
            std::string tenantId;

        public:
            Family();
            Family(int id, const std::string& headName, const std::string& address,
                   const std::string& contact, int memberCount, bool displaced,
                   const std::string& tenantId = "");

            void setHeadName(const std::string& headName);
            void setAddress(const std::string& address);
            void setContact(const std::string& contact);
            void setMemberCount(int memberCount);
            void setDisplaced(bool displaced);
            void setTenantId(const std::string& tenantId);

            std::string getHeadName() const;
            std::string getAddress() const;
            std::string getContact() const;
            int getMemberCount() const;
            bool isDisplaced() const;
            std::string getTenantId() const;

            std::string toString() const override;
        };
    }
}