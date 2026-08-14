#pragma once
#include <string>
#include "../core/BaseEntity.h"

namespace AgroResQ
{
    namespace Entities
    {
        class Report : public Core::BaseEntity
        {
        private:
            std::string title;
            std::string description;
            std::string date;
            std::string tenantId;

        public:
            Report();
            Report(int id, const std::string& title, const std::string& description,
                   const std::string& date, const std::string& tenantId = "");

            void setTitle(const std::string& title);
            void setDescription(const std::string& description);
            void setDate(const std::string& date);
            void setTenantId(const std::string& tenantId);

            std::string getTitle() const;
            std::string getDescription() const;
            std::string getDate() const;
            std::string getTenantId() const;

            std::string toString() const override;
        };
    }
}