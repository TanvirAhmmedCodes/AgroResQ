#include "ShelterAllocator.h"

namespace AgroResQ
{
namespace Algorithms
{

ShelterAllocator::ShelterAllocator() = default;

int ShelterAllocator::allocateShelter(
    const Entities::Victim& victim) const
{
    if(victim.isMissing())
        return -1;

    if(victim.isDisabled())
        return 1;

    if(victim.isVulnerable())
        return 2;

    return 3;
}

}
}