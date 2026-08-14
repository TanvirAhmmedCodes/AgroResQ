#include "LicenseManager.h"
namespace AgroResQ
{
namespace Business
{
LicenseManager::LicenseManager(LicenseTier t) : tier(t) {}
void LicenseManager::setTier(LicenseTier t) { tier = t; }
LicenseTier LicenseManager::getTier() const { return tier; }
bool LicenseManager::canAccess(Feature f) const
{
    if (tier == LicenseTier::GOVERNMENT) return true;
    if (tier == LicenseTier::NGO)
    {
        if (f == Feature::PARTNER_ANALYTICS) return false;
        return true;
    }
    if (tier == LicenseTier::PREMIUM)
    {
        if (f == Feature::PARTNER_ANALYTICS) return false;
        if (f == Feature::EXPORT_REPORT) return true;
        return true;
    }
    if (tier == LicenseTier::FREE)
    {
        if (f == Feature::DISASTER_ADD) return false;
        if (f == Feature::PARTNER_ANALYTICS) return false;
        if (f == Feature::EXPORT_REPORT) return false;
        if (f == Feature::SENSOR_SYNC) return false;
        if (f == Feature::SENSOR_VIEW) return true;
        if (f == Feature::CROP_RECOMMEND) return true;
        return false;
    }
    return false;
}
}
}