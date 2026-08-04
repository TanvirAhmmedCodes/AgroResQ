#include "Family.h"
#include <sstream>

namespace AgroResQ
{
    namespace Entities
    {
        Family::Family() : memberCount(0), displaced(false) {}

        Family::Family(int id, const std::string& headName, const std::string& address,
                       const std::string& contact, int memberCount, bool displaced)
        {
            setId(id);
            this->headName = headName;
            this->address = address;
            this->contact = contact;
            this->memberCount = memberCount;
            this->displaced = displaced;
        }

        void Family::setHeadName(const std::string& headName)
        {
            this->headName = headName;
        }

        void Family::setAddress(const std::string& address)
        {
            this->address = address;
        }

        void Family::setContact(const std::string& contact)
        {
            this->contact = contact;
        }

        void Family::setMemberCount(int memberCount)
        {
            this->memberCount = memberCount;
        }

        void Family::setDisplaced(bool displaced)
        {
            this->displaced = displaced;
        }

        std::string Family::getHeadName() const
        {
            return headName;
        }

        std::string Family::getAddress() const
        {
            return address;
        }

        std::string Family::getContact() const
        {
            return contact;
        }

        int Family::getMemberCount() const
        {
            return memberCount;
        }

        bool Family::isDisplaced() const
        {
            return displaced;
        }

        std::string Family::toString() const
        {
            std::stringstream ss;
            ss << getId() << ","
               << headName << ","
               << address << ","
               << contact << ","
               << memberCount << ","
               << displaced;
            return ss.str();
        }
    }
}