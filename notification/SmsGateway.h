#pragma once
#include <string>
#include <vector>
#include "../core/FileManager.h"

namespace AgroResQ
{
namespace Notification
{

class SmsGateway
{
private:
    Core::FileManager fileManager;
    std::string contactsFilePath;

    std::vector<std::string> loadContacts();

public:
    SmsGateway();
    explicit SmsGateway(const std::string& contactsFile);

    bool sendSms(const std::string& phoneNumber, const std::string& message);
    bool sendBulkSms(const std::vector<std::string>& numbers, const std::string& message);
    bool sendAlertToAllContacts(const std::string& alertTitle, const std::string& alertMessage);
    bool addContact(const std::string& phoneNumber);
};

}
}