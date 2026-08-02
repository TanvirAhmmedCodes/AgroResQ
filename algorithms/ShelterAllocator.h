#pragma once

#include "../entities/Victim.h"

namespace AgroResQ
{
namespace Algorithms
{

class ShelterAllocator
{
public:
    ShelterAllocator();

    int allocateShelter(
        const Entities::Victim& victim) const;
};

}
}