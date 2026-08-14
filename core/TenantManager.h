#ifndef AGRO_RESQ_TENANT_MANAGER_H
#define AGRO_RESQ_TENANT_MANAGER_H

#include <string>
#include <vector>

namespace AgroResQ
{
namespace Core
{

class TenantManager
{
private:
    static std::string currentTenantId;
    static std::vector<std::string> allowedTenants;

public:
    static void setCurrentTenant(const std::string& tenantId);
    static std::string getCurrentTenant();
    static bool isTenantAllowed(const std::string& tenantId);
    static void setAllowedTenants(const std::vector<std::string>& tenants);
    static bool hasAccessTo(const std::string& resourceTenantId);
    static bool isGlobalAdmin();
};

}
}

#endif