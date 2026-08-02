#pragma once
#include <string>
#include <vector>
#include "../entities/Disaster.h"
#include "../entities/Victim.h"

namespace AgroResQ
{
    namespace Algorithms
    {
        struct Alert
        {
            int id;
            std::string title;
            std::string message;
            std::string timestamp;
            std::string severity;
            bool isRead;

            Alert() : id(0), isRead(false) {}
            Alert(int i, const std::string& t, const std::string& m,
                  const std::string& ts, const std::string& s)
                : id(i), title(t), message(m), timestamp(ts), severity(s), isRead(false) {}
        };

        class AlertSystem
        {
        private:
            std::vector<Alert> alerts;
            int nextId;

        public:
            AlertSystem();

            void sendDisasterAlert(const Entities::Disaster& disaster);
            void sendMissingPersonAlert(const Entities::Victim& victim);
            void sendCriticalAlert(const std::string& title, const std::string& message);
            void sendGeneralAlert(const std::string& title, const std::string& message);

            std::vector<Alert> getAllAlerts() const;
            std::vector<Alert> getUnreadAlerts() const;
            std::vector<Alert> getAlertsBySeverity(const std::string& severity) const;
            void markAsRead(int alertId);
            void markAllAsRead();
            void displayAlerts() const;
            void displayUnreadAlerts() const;
        };
    }
}