#include "AlertSystem.h"
#include <iostream>
#include <ctime>
#include <iomanip>

namespace AgroResQ
{
    namespace Algorithms
    {
        AlertSystem::AlertSystem() : nextId(1) {}

        std::string getCurrentTime()
        {
            time_t now = time(nullptr);
            char buf[80];
            strftime(buf, sizeof(buf), "%Y-%m-%d %H:%M:%S", localtime(&now));
            return std::string(buf);
        }

        void AlertSystem::sendDisasterAlert(const Entities::Disaster& disaster)
        {
            std::string title = "DISASTER ALERT: " + disaster.getName();
            std::string message = "A " + disaster.getType() + " disaster has been reported in "
                                + disaster.getLocation() + ". Severity: " + std::to_string(disaster.getSeverity())
                                + "/10. Date: " + disaster.getDate();
            std::string severity = disaster.getSeverity() >= 7 ? "CRITICAL" : "HIGH";

            alerts.push_back(Alert(nextId++, title, message, getCurrentTime(), severity));
        }

        void AlertSystem::sendMissingPersonAlert(const Entities::Victim& victim)
        {
            std::string title = "MISSING PERSON ALERT";
            std::string message = "Victim " + victim.getName() + " (ID: " + std::to_string(victim.getId())
                                + ") is missing from " + victim.getAddress()
                                + ". Age: " + std::to_string(victim.getAge())
                                + ". Please report if found.";

            alerts.push_back(Alert(nextId++, title, message, getCurrentTime(), "CRITICAL"));
        }

        void AlertSystem::sendCriticalAlert(const std::string& title, const std::string& message)
        {
            alerts.push_back(Alert(nextId++, "CRITICAL: " + title, message, getCurrentTime(), "CRITICAL"));
        }

        void AlertSystem::sendGeneralAlert(const std::string& title, const std::string& message)
        {
            alerts.push_back(Alert(nextId++, title, message, getCurrentTime(), "NORMAL"));
        }

        std::vector<Alert> AlertSystem::getAllAlerts() const
        {
            return alerts;
        }

        std::vector<Alert> AlertSystem::getUnreadAlerts() const
        {
            std::vector<Alert> unread;
            for (const auto& alert : alerts)
            {
                if (!alert.isRead)
                    unread.push_back(alert);
            }
            return unread;
        }

        std::vector<Alert> AlertSystem::getAlertsBySeverity(const std::string& severity) const
        {
            std::vector<Alert> result;
            for (const auto& alert : alerts)
            {
                if (alert.severity == severity)
                    result.push_back(alert);
            }
            return result;
        }

        void AlertSystem::markAsRead(int alertId)
        {
            for (auto& alert : alerts)
            {
                if (alert.id == alertId)
                {
                    alert.isRead = true;
                    break;
                }
            }
        }

        void AlertSystem::markAllAsRead()
        {
            for (auto& alert : alerts)
            {
                alert.isRead = true;
            }
        }

        void AlertSystem::displayAlerts() const
        {
            if (alerts.empty())
            {
                std::cout << "\nNo Alerts.\n";
                return;
            }

            std::cout << "\n============================================================\n";
            std::cout << "                     ALERT SYSTEM\n";
            std::cout << "============================================================\n";

            for (const auto& alert : alerts)
            {
                std::cout << "\n[" << alert.severity << "] " << alert.title << "\n";
                std::cout << "ID: " << alert.id << " | Time: " << alert.timestamp << "\n";
                std::cout << "Message: " << alert.message << "\n";
                std::cout << "Status: " << (alert.isRead ? "Read" : "Unread") << "\n";
                std::cout << "------------------------------------------------------------\n";
            }
        }

        void AlertSystem::displayUnreadAlerts() const
        {
            auto unread = getUnreadAlerts();
            if (unread.empty())
            {
                std::cout << "\nNo Unread Alerts.\n";
                return;
            }

            std::cout << "\n============================================================\n";
            std::cout << "                 UNREAD ALERTS (" << unread.size() << ")\n";
            std::cout << "============================================================\n";

            for (const auto& alert : unread)
            {
                std::cout << "\n[" << alert.severity << "] " << alert.title << "\n";
                std::cout << "ID: " << alert.id << " | Time: " << alert.timestamp << "\n";
                std::cout << "Message: " << alert.message << "\n";
                std::cout << "------------------------------------------------------------\n";
            }
        }
    }
}