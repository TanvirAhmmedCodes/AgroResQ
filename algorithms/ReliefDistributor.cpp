#include "ReliefDistributor.h"

namespace AgroResQ
{
namespace Algorithms
{

ReliefDistributor::ReliefDistributor() = default;

bool ReliefDistributor::shouldReceiveRelief(
    const Entities::Victim& victim) const
{
    if(victim.isMissing())
        return false;

    if(victim.isRescued() &&
       victim.getPriorityScore() >= 50)
    {
        return true;
    }

    return false;
}

}
}