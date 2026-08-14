#ifndef AGRO_RESQ_AUTH_MANAGER_H
#define AGRO_RESQ_AUTH_MANAGER_H

#include <string>
#include <vector>
#include <cstdint>

namespace AgroResQ
{
namespace Core
{

enum class UserRole
{
    ADMIN,
    NGO_OPERATOR,
    FARMER
};

struct User
{
    int id;
    std::string username;
    std::string passwordHash;
    UserRole role;
    std::string tenantId;
    bool isLoggedIn;

    User() : id(0), role(UserRole::FARMER), isLoggedIn(false) {}
};

class AuthManager
{
private:
    static User currentUser;
    static std::string usersFilePath;
    static std::string hashPassword(const std::string& password, const std::string& salt);
    static std::string generateSalt();
    static User parseUserLine(const std::string& line);
    static std::string serializeUser(const User& user);
    static std::string roleToString(UserRole role);
    static UserRole stringToRole(const std::string& roleStr);

public:
    static bool initialize(const std::string& filePath = "database/users.txt");
    static bool registerUser(const std::string& username, const std::string& password, UserRole role, const std::string& tenantId);
    static bool login(const std::string& username, const std::string& password);
    static void logout();
    static User getCurrentUser();
    static bool isLoggedIn();
    static bool hasRole(UserRole role);
    static bool isAdmin();
    static bool isNGO();
    static bool isFarmer();
    static bool changePassword(const std::string& username, const std::string& oldPassword, const std::string& newPassword);
    static std::vector<User> getAllUsers();
    static bool deleteUser(int userId);
    static bool updateUserRole(int userId, UserRole newRole);
};

}
}

#endif