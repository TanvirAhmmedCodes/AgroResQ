#pragma once
#include <string>
#include "../core/BaseEntity.h"

namespace AgroResQ
{
    namespace Entities
    {
        class RescueTeam : public Core::BaseEntity
        {
        private:
            std::string teamName;
            std::string leaderName;
            std::string location;
            int members;
            bool available;
            std::string tenantId;

        public:
            RescueTeam();
            RescueTeam(int id, const std::string& teamName, const std::string& leaderName,
                       const std::string& location, int members, bool available,
                       const std::string& tenantId = "");

            void setTeamName(const std::string& teamName);
            void setLeaderName(const std::string& leaderName);
            void setLocation(const std::string& location);
            void setMembers(int members);
            void setAvailable(bool available);
            void setTenantId(const std::string& tenantId);

            std::string getTeamName() const;
            std::string getLeaderName() const;
            std::string getLocation() const;
            int getMembers() const;
            bool isAvailable() const;
            std::string getTenantId() const;

            std::string toString() const override;
        };
    }
}