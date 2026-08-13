#pragma once

#include <string>
#include <vector>

#include "../entities/Crop.h"
#include "../entities/Soil.h"

namespace AgroResQ
{
namespace Algorithms
{

class CropRecommendation
{
private:

    double calculateScore(
        const Entities::Crop& crop,
        const Entities::Soil& soil) const;


public:

    CropRecommendation();

    std::vector<Entities::Crop> recommend(
        const std::vector<Entities::Crop>& crops,
        const Entities::Soil& soil) const;
};

}
}