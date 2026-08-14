#include "Family.h"
#include <sstream>

namespace AgroResQ
{
    namespace Entities
    {
        Family::Family() : memberCount(0), displaced(false) {}

        Family::Family(int id, const std::string& headName, const std::string& address,
                       const std::string& contact, int memberCount, bool displaced,
                       const std::string& tenantId)
        {
            setId(id);
            this->headName = headName;
            this->address = address;
            this->contact = contact;
            this->memberCount = memberCount;
            this->displaced = displaced;
            this->tenantId = tenantId;
        }

        void Family::setHeadName(const std::string& headName) { this->headName = headName; }
        void Family::setAddress(const std::string& address) { this->address = address; }
        void Family::setContact(const std::string& contact) { this->contact = contact; }
        void Family::setMemberCount(int memberCount) { this->memberCount = memberCount; }
        void Family::setDisplaced(bool displaced) { this->displaced = displaced; }
        void Family::setTenantId(const std::string& tenantId) { this->tenantId = tenantId; }

        std::string Family::getHeadName() const { return headName; }
        std::string Family::getAddress() const { return address; }
        std::string Family::getContact() const { return contact; }
        int Family::getMemberCount() const { return memberCount; }
        bool Family::isDisplaced() const { return displaced; }
        std::string Family::getTenantId() const { return tenantId; }

        std::string Family::toString() const
        {
            std::stringstream ss;
            ss << getId() << "," << headName << "," << address << ","
               << contact << "," << memberCount << "," << displaced << ","
               << tenantId;
            return ss.str();
        }
    }
}