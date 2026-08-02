#include "PriorityCalculator.h"

namespace AgroResQ
{
namespace Algorithms
{

PriorityCalculator::PriorityCalculator() = default;



double PriorityCalculator::calculateDisasterScore(
    const Entities::Disaster& disaster) const
{
    double score = 0;


    score += disaster.getSeverity() * 10;


    return score;
}



double PriorityCalculator::calculateVictimScore(
    const Entities::Victim& victim) const
{
    double score = 0;

    if(victim.isVulnerable())
        score += 20;

    if(victim.isDisabled())
        score += 20;

    if(victim.isMissing())
        score += 20;

    if(!victim.isRescued())
        score += 15;

    if(!victim.hasReliefReceived())
        score += 15;

    if(victim.getAge() <= 12)
        score += 10;

    if(victim.getAge() >= 60)
        score += 10;

    if(victim.getHealthStatus() == "Critical")
        score += 20;
    else if(victim.getHealthStatus() == "Injured")
        score += 10;

    if(score > 100)
        score = 100;

    return score;
}



double PriorityCalculator::calculateDisasterPriority(
    const Entities::Disaster& disaster) const
{
    return calculateDisasterScore(disaster);
}



double PriorityCalculator::calculateVictimPriority(
    const Entities::Victim& victim) const
{
    return calculateVictimScore(victim);
}

}
}