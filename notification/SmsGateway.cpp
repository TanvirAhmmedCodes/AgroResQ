#include "SmsGateway.h"
#include <iostream>
#include <fstream>
#include <sstream>
namespace AgroResQ
{
namespace Notification
{
SmsGateway::SmsGateway()
{
    contactsFilePath = "database/contacts.txt";
    fileManager.createFile(contactsFilePath);
    std::vector<std::string> existing = loadContacts();
    if (existing.empty())
    {
        addContact("+8801712345678");
        addContact("+8801812345679");
        addContact("+8801912345670");
        addContact("+8801612345671");
        addContact("+8801976543210");
    }
}
SmsGateway::SmsGateway(const std::string& contactsFile)
    : contactsFilePath(contactsFile)
{
    fileManager.createFile(contactsFilePath);
    std::vector<std::string> existing = loadContacts();
    if (existing.empty())
    {
        addContact("+8801712345678");
        addContact("+8801812345679");
        addContact("+8801912345670");
        addContact("+8801612345671");
        addContact("+8801976543210");
    }
}
std::vector<std::string> SmsGateway::loadContacts()
{
    std::vector<std::string> contacts;
    std::vector<std::string> lines = fileManager.readLines(contactsFilePath);
    for (const std::string& line : lines)
    {
        if (!line.empty())
        {
            contacts.push_back(line);
        }
    }
    return contacts;
}
bool SmsGateway::addContact(const std::string& phoneNumber)
{
    if (phoneNumber.empty()) return false;
    return fileManager.appendFile(contactsFilePath, phoneNumber + "\n");
}
bool SmsGateway::sendSms(const std::string& phoneNumber, const std::string& message)
{
    if (phoneNumber.empty() || message.empty()) return false;
    std::cout << "\n============================================================\n";
    std::cout << "[SMS GATEWAY] SIMULATED SMS SENT\n";
    std::cout << "To: " << phoneNumber << "\n";
    std::cout << "Msg: " << message << "\n";
    std::cout << "============================================================\n";
    return true;
}
bool SmsGateway::sendBulkSms(const std::vector<std::string>& numbers, const std::string& message)
{
    bool allSent = true;
    for (const std::string& num : numbers)
    {
        if (!sendSms(num, message))
        {
            allSent = false;
        }
    }
    return allSent;
}
bool SmsGateway::sendAlertToAllContacts(const std::string& alertTitle, const std::string& alertMessage)
{
    std::vector<std::string> contacts = loadContacts();
    if (contacts.empty())
    {
        std::cout << "[SMS Gateway] No contacts found.\n";
        return false;
    }
    std::string fullMessage = "ALERT: " + alertTitle + " - " + alertMessage;
    return sendBulkSms(contacts, fullMessage);
}
}
}