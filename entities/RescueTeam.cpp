#include "RescueTeam.h"
#include <sstream>

namespace AgroResQ
{
    namespace Entities
    {
        RescueTeam::RescueTeam() : members(0), available(true) {}

        RescueTeam::RescueTeam(int id, const std::string& teamName, const std::string& leaderName,
                               const std::string& location, int members, bool available,
                               const std::string& tenantId)
        {
            setId(id);
            this->teamName = teamName;
            this->leaderName = leaderName;
            this->location = location;
            this->members = members;
            this->available = available;
            this->tenantId = tenantId;
        }

        void RescueTeam::setTeamName(const std::string& teamName) { this->teamName = teamName; }
        void RescueTeam::setLeaderName(const std::string& leaderName) { this->leaderName = leaderName; }
        void RescueTeam::setLocation(const std::string& location) { this->location = location; }
        void RescueTeam::setMembers(int members) { this->members = members; }
        void RescueTeam::setAvailable(bool available) { this->available = available; }
        void RescueTeam::setTenantId(const std::string& tenantId) { this->tenantId = tenantId; }

        std::string RescueTeam::getTeamName() const { return teamName; }
        std::string RescueTeam::getLeaderName() const { return leaderName; }
        std::string RescueTeam::getLocation() const { return location; }
        int RescueTeam::getMembers() const { return members; }
        bool RescueTeam::isAvailable() const { return available; }
        std::string RescueTeam::getTenantId() const { return tenantId; }

        std::string RescueTeam::toString() const
        {
            std::stringstream stream;
            stream << getId() << "," << teamName << "," << leaderName << ","
                   << location << "," << members << "," << available << ","
                   << tenantId;
            return stream.str();
        }
    }
}