#include "TenantManager.h"
#include "AuthManager.h"

namespace AgroResQ
{
namespace Core
{

std::string TenantManager::currentTenantId = "";
std::vector<std::string> TenantManager::allowedTenants = {};

void TenantManager::setCurrentTenant(const std::string& tenantId)
{
    currentTenantId = tenantId;
}

std::string TenantManager::getCurrentTenant()
{
    return currentTenantId;
}

bool TenantManager::isTenantAllowed(const std::string& tenantId)
{
    if (allowedTenants.empty()) return true;
    for (const auto& t : allowedTenants)
    {
        if (t == tenantId) return true;
    }
    return false;
}

void TenantManager::setAllowedTenants(const std::vector<std::string>& tenants)
{
    allowedTenants = tenants;
}

bool TenantManager::hasAccessTo(const std::string& resourceTenantId)
{
    if (!AuthManager::isLoggedIn()) return false;
    if (AuthManager::isAdmin()) return true;
    return (currentTenantId == resourceTenantId);
}

bool TenantManager::isGlobalAdmin()
{
    return AuthManager::isLoggedIn() && AuthManager::isAdmin();
}

}
}