#include "AuthManager.h"
#include "FileManager.h"
#include "IDGenerator.h"
#include "StringHelper.h"
#include <sstream>
#include <ctime>
#include <cstdlib>

namespace AgroResQ
{
namespace Core
{

User AuthManager::currentUser;
std::string AuthManager::usersFilePath = "database/users.txt";

static const std::string SALT_CHARS = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
static const uint32_t HASH_KEY = 0x9E3779B1;

std::string AuthManager::hashPassword(const std::string& password, const std::string& salt)
{
    std::string combined = salt + password;
    uint32_t hash = 0;
    for (size_t i = 0; i < combined.length(); ++i)
    {
        hash = (hash * 31) + static_cast<unsigned char>(combined[i]);
        hash ^= (hash >> 13) ^ (hash << 19);
        hash ^= HASH_KEY;
    }
    std::stringstream ss;
    ss << std::hex << hash;
    return salt + ":" + ss.str();
}

std::string AuthManager::generateSalt()
{
    std::string salt;
    salt.reserve(8);
    for (int i = 0; i < 8; ++i)
    {
        salt += SALT_CHARS[rand() % SALT_CHARS.length()];
    }
    return salt;
}

std::string AuthManager::roleToString(UserRole role)
{
    if (role == UserRole::ADMIN) return "ADMIN";
    if (role == UserRole::NGO_OPERATOR) return "NGO_OPERATOR";
    return "FARMER";
}

UserRole AuthManager::stringToRole(const std::string& roleStr)
{
    if (roleStr == "ADMIN") return UserRole::ADMIN;
    if (roleStr == "NGO_OPERATOR") return UserRole::NGO_OPERATOR;
    return UserRole::FARMER;
}

User AuthManager::parseUserLine(const std::string& line)
{
    std::stringstream ss(line);
    User user;
    std::string roleStr;
    std::string idStr;
    std::getline(ss, idStr, ',');
    std::getline(ss, user.username, ',');
    std::getline(ss, user.passwordHash, ',');
    std::getline(ss, roleStr, ',');
    std::getline(ss, user.tenantId, ',');
    user.id = safeStoi(idStr);
    user.role = stringToRole(roleStr);
    user.isLoggedIn = false;
    return user;
}

std::string AuthManager::serializeUser(const User& user)
{
    std::stringstream ss;
    ss << user.id << ","
       << user.username << ","
       << user.passwordHash << ","
       << roleToString(user.role) << ","
       << user.tenantId;
    return ss.str();
}

bool AuthManager::initialize(const std::string& filePath)
{
    usersFilePath = filePath;
    FileManager fm;
    if (!fm.fileExists(usersFilePath))
    {
        fm.createFile(usersFilePath);
        User admin;
        admin.username = "admin";
        admin.role = UserRole::ADMIN;
        admin.tenantId = "ALL";
        std::string salt = generateSalt();
        admin.passwordHash = hashPassword("admin123", salt);
        admin.id = 1;
        fm.appendFile(usersFilePath, serializeUser(admin) + "\n");
        return true;
    }
    return true;
}

bool AuthManager::registerUser(const std::string& username, const std::string& password, UserRole role, const std::string& tenantId)
{
    if (username.empty() || password.length() < 4) return false;
    FileManager fm;
    std::vector<std::string> lines = fm.readLines(usersFilePath);
    for (const auto& line : lines)
    {
        if (line.empty()) continue;
        User existing = parseUserLine(line);
        if (existing.username == username) return false;
    }
    int newId = IDGenerator().generateNextId(usersFilePath);
    User newUser;
    newUser.id = newId;
    newUser.username = username;
    newUser.role = role;
    newUser.tenantId = tenantId;
    std::string salt = generateSalt();
    newUser.passwordHash = hashPassword(password, salt);
    return fm.appendFile(usersFilePath, serializeUser(newUser) + "\n");
}

bool AuthManager::login(const std::string& username, const std::string& password)
{
    FileManager fm;
    std::vector<std::string> lines = fm.readLines(usersFilePath);
    for (const auto& line : lines)
    {
        if (line.empty()) continue;
        User user = parseUserLine(line);
        if (user.username == username)
        {
            std::string storedHash = user.passwordHash;
            size_t colonPos = storedHash.find(':');
            if (colonPos == std::string::npos) continue;
            std::string salt = storedHash.substr(0, colonPos);
            std::string checkHash = hashPassword(password, salt);
            if (checkHash == storedHash)
            {
                currentUser = user;
                currentUser.isLoggedIn = true;
                return true;
            }
        }
    }
    return false;
}

void AuthManager::logout()
{
    currentUser = User();
    currentUser.isLoggedIn = false;
}

User AuthManager::getCurrentUser()
{
    return currentUser;
}

bool AuthManager::isLoggedIn()
{
    return currentUser.isLoggedIn;
}

bool AuthManager::hasRole(UserRole role)
{
    if (!isLoggedIn()) return false;
    return currentUser.role == role || currentUser.role == UserRole::ADMIN;
}

bool AuthManager::isAdmin()
{
    return hasRole(UserRole::ADMIN);
}

bool AuthManager::isNGO()
{
    return hasRole(UserRole::NGO_OPERATOR);
}

bool AuthManager::isFarmer()
{
    return hasRole(UserRole::FARMER);
}

bool AuthManager::changePassword(const std::string& username, const std::string& oldPassword, const std::string& newPassword)
{
    FileManager fm;
    std::vector<std::string> lines = fm.readLines(usersFilePath);
    std::string newData;
    bool found = false;
    for (const auto& line : lines)
    {
        if (line.empty()) continue;
        User user = parseUserLine(line);
        if (user.username == username)
        {
            std::string storedHash = user.passwordHash;
            size_t colonPos = storedHash.find(':');
            if (colonPos == std::string::npos) continue;
            std::string salt = storedHash.substr(0, colonPos);
            if (hashPassword(oldPassword, salt) != storedHash) return false;
            std::string newSalt = generateSalt();
            user.passwordHash = hashPassword(newPassword, newSalt);
            found = true;
        }
        newData += serializeUser(user) + "\n";
    }
    if (!found) return false;
    return fm.writeFile(usersFilePath, newData);
}

std::vector<User> AuthManager::getAllUsers()
{
    FileManager fm;
    std::vector<User> users;
    std::vector<std::string> lines = fm.readLines(usersFilePath);
    for (const auto& line : lines)
    {
        if (line.empty()) continue;
        users.push_back(parseUserLine(line));
    }
    return users;
}

bool AuthManager::deleteUser(int userId)
{
    FileManager fm;
    std::vector<std::string> lines = fm.readLines(usersFilePath);
    std::string newData;
    bool removed = false;
    for (const auto& line : lines)
    {
        if (line.empty()) continue;
        User user = parseUserLine(line);
        if (user.id == userId)
        {
            removed = true;
            if (currentUser.id == userId) logout();
            continue;
        }
        newData += serializeUser(user) + "\n";
    }
    if (!removed) return false;
    return fm.writeFile(usersFilePath, newData);
}

bool AuthManager::updateUserRole(int userId, UserRole newRole)
{
    FileManager fm;
    std::vector<std::string> lines = fm.readLines(usersFilePath);
    std::string newData;
    bool updated = false;
    for (const auto& line : lines)
    {
        if (line.empty()) continue;
        User user = parseUserLine(line);
        if (user.id == userId)
        {
            user.role = newRole;
            updated = true;
        }
        newData += serializeUser(user) + "\n";
    }
    if (!updated) return false;
    return fm.writeFile(usersFilePath, newData);
}

}
}