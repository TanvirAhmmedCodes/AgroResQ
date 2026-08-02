#pragma once

#include "../entities/Victim.h"

namespace AgroResQ
{
namespace Algorithms
{

class ReliefDistributor
{
public:

    ReliefDistributor();

    bool shouldReceiveRelief(
        const Entities::Victim& victim) const;
};

}
}