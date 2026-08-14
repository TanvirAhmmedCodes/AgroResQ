#pragma once
#include <string>
namespace AgroResQ
{
namespace Business
{
enum class LicenseTier
{
    FREE,
    PREMIUM,
    NGO,
    GOVERNMENT
};
enum class Feature
{
    DISASTER_ADD,
    VICTIM_ADD,
    SENSOR_VIEW,
    SENSOR_SYNC,
    CROP_RECOMMEND,
    PARTNER_ANALYTICS,
    EXPORT_REPORT
};
class LicenseManager
{
private:
    LicenseTier tier;
public:
    LicenseManager(LicenseTier t = LicenseTier::FREE);
    void setTier(LicenseTier t);
    LicenseTier getTier() const;
    bool canAccess(Feature f) const;
};
}
}